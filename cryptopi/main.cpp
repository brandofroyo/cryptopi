#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WComboBox>
#include <Wt/WTable>
#include <Wt/WTimer>
#include <Wt/WCheckBox>
#include <algorithm>
#include <unistd.h>
#include "TradePair.h"


using namespace Wt;
using namespace std;

// This is the main window for the app
class CryptoPiMain : public WApplication
{
// Public methods
public:
	CryptoPiMain(const WEnvironment& env);
	void addToMonitor();
	void updateTable();
	void resetTable();
	void updatePairs();

// private variables
private:
	WLineEdit *pairList_;
	WText *cryptoInfo_;
	WComboBox *interval_;
	WTable *table_;
	WTimer *timer_;
	WCheckBox *bittrexCheck_;
	WCheckBox *bitfinCheck_;
	WCheckBox *gdaxCheck_;
	vector<TradePair> pairs_;
};


// Main window constructor
CryptoPiMain::CryptoPiMain(const WEnvironment& env)
	: WApplication(env)
{
	setTitle("CryptoPi Main Menu");                               // application title

	// Add a text label
	root()->addWidget(new WText("Enter trade pair(s) that you would like to monitor, separated by comma (e.g. BTC-LTC,BTC-ETC): "));  // show some text

	root()->addWidget(new WBreak());                       // insert a line break

	pairList_ = new WLineEdit(root());                     // allow text input
	pairList_->setFocus();                                 // give focus to the main input

	root()->addWidget(new WText("\t every \t"));  // show some text
	// This is the dropdown menu that allows the user to select the refresh interval
	interval_ = new WComboBox(root());
	interval_->addItem("30 sec");
	interval_->addItem("1 min");
	interval_->addItem("15 min");
	interval_->addItem("30 min");
	interval_->addItem("1 hour");

	// line break
	root()->addWidget(new WBreak());                       // insert a line break
	root()->addWidget(new WText("Include information from the following exchanges:"));  // information about the following checkboxes
	root()->addWidget(new WBreak());                       // insert a line break
	// checkboxes for exchange toggles
	bittrexCheck_ = new WCheckBox(root());
	bittrexCheck_->setInline(false);
	bittrexCheck_->setText("Bittrex");
	bitfinCheck_ = new WCheckBox(root());
	bitfinCheck_->setInline(false);
	bitfinCheck_->setText("Bitfinex");
	gdaxCheck_ = new WCheckBox(root());
	gdaxCheck_->setInline(false);
	gdaxCheck_->setText("GDax");

	root()->addWidget(new WBreak());                       // insert a line break
	root()->addWidget(new WBreak());                       // insert a line break

	WPushButton *button = new WPushButton("Start Monitoring", root());              // create a button
	button->setMargin(5, Left);                            // add 5 pixels margin

	root()->addWidget(new WBreak());                       // insert a line break
	root()->addWidget(new WBreak());                       // insert a line break

	cryptoInfo_ = new WText(root());                         // start with empty text

	root()->addWidget(new WBreak());                       // insert a line break

	// table to display the results
	table_ = new WTable(root());

	// timer to keep track of refresh
	timer_ = new WTimer(root());
	timer_->timeout().connect(this, &CryptoPiMain::updatePairs);

	// Bind the button push to the function
	button->clicked().connect(this, &CryptoPiMain::addToMonitor);

	// Bind to the Enter key when focused on the text to the function
	pairList_->enterPressed().connect(boost::bind(&CryptoPiMain::addToMonitor, this));
}

// function hooked to submit button
void CryptoPiMain::addToMonitor()
{
	// stop the timer because we do not want another loop while in this function
	timer_->stop();
	// fetch all the user input and parse it
	std::string t = pairList_->text().toUTF8();
	std::string newText;
	std::stringstream ss;

	pairs_.clear();
	std::string delimiter = ",";

	// count how many pairs user inputted and push them onto a vector
	size_t pos = 0;
	std::string token;
	while ((pos = t.find(delimiter)) != std::string::npos) {
		token = t.substr(0, pos);
		pairs_.push_back(TradePair(token, bittrexCheck_->isChecked(), bitfinCheck_->isChecked(), gdaxCheck_->isChecked()));
		t.erase(0, pos + delimiter.length());
	}
	pairs_.push_back(TradePair(t, bittrexCheck_->isChecked(), bitfinCheck_->isChecked(), gdaxCheck_->isChecked()));

	ss << "You have chosen to monitor " << pairs_.size() << " pairs:";
	newText = ss.str();
	// update information textbox
	cryptoInfo_->setText(newText);

	// update time interval input by the user
	int timeInterval = 0;

	switch(interval_->currentIndex()){
		case 0:
			timeInterval = 30;
		case 1:
			timeInterval = 60;
		case 2:
			timeInterval = 900;
		case 3:
			timeInterval = 1800;
		case 4:
			timeInterval = 3600;
		default:
			break;
	}

	// reset the timer
	timer_->setInterval(timeInterval*1000);
	timer_->start();

	// update the table
	CryptoPiMain::updateTable();
}

// get names, volumes, prices, and changes from the backend and update the table accordingly
void CryptoPiMain::updateTable()
{
	CryptoPiMain::resetTable();
	int n = pairs_.size();
	for (int i = 0; i < n; i++){
		WTableCell *nameCell = table_->elementAt(i+1, 0);
		WTableCell *volCell = table_->elementAt(i+1, 1);
		WTableCell *volChangeCell = table_->elementAt(i+1, 2);
		WTableCell *priceCell = table_->elementAt(i+1, 3);
		WTableCell *priceChangeCell = table_->elementAt(i+1, 4);

		std::string name = pairs_[i].getName();
		std::string volume = pairs_[i].getVolumes();
		std::string volumeChange = pairs_[i].getVolumeChanges();
		std::string price = pairs_[i].getPrices();
		std::string priceChange = pairs_[i].getPriceChanges();

		nameCell->addWidget(new WText(name));
		volCell->addWidget(new WText(volume));
		volChangeCell->addWidget(new WText(volumeChange));
		priceCell->addWidget(new WText(price));
		priceChangeCell->addWidget(new WText(priceChange));

	}
}

// this method gets called by the timer only and does the same thing as above method but without resetting the table
void CryptoPiMain::updatePairs()
{
	int n = pairs_.size();
	for (int i = 0; i < n; i++){
		WTableCell *nameCell = table_->elementAt(i+1, 0);
		WTableCell *volCell = table_->elementAt(i+1, 1);
		WTableCell *volChangeCell = table_->elementAt(i+1, 2);
		WTableCell *priceCell = table_->elementAt(i+1, 3);
		WTableCell *priceChangeCell = table_->elementAt(i+1, 4);

		std::string name = pairs_[i].getName();
		std::string volumeChange = pairs_[i].getVolumeChanges();
		std::string priceChange = pairs_[i].getPriceChanges();

		pairs_[i].updateVolumes();
		pairs_[i].updatePrices();
		std::string volume = pairs_[i].getVolumes();
		std::string price = pairs_[i].getPrices();

		nameCell->clear();
		volCell->clear();
		volChangeCell->clear();
		priceCell->clear();
		priceChangeCell->clear();
		nameCell->addWidget(new WText(name));
		volCell->addWidget(new WText(volume));
		volChangeCell->addWidget(new WText(volumeChange));
		priceCell->addWidget(new WText(price));
		priceChangeCell->addWidget(new WText(priceChange));

	}
}

// clear the table and reinitialize it
void CryptoPiMain::resetTable()
{
	table_->clear();
	table_->setHeaderCount(1);
	table_->setWidth(WLength("100%"));
	table_->elementAt(0,0)->addWidget(new WText("Pair"));
	table_->elementAt(0,1)->addWidget(new WText("Volume"));
	table_->elementAt(0,2)->addWidget(new WText("Volume Change"));
	table_->elementAt(0,3)->addWidget(new WText("Price"));
	table_->elementAt(0,4)->addWidget(new WText("Price Change"));
}

// create the main window
WApplication *createApplication(const WEnvironment& env)
{

	return new CryptoPiMain(env);
}

// run the application
int main(int argc, char **argv)
{
	return WRun(argc, argv, &createApplication);
}

