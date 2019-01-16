#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WComboBox>
#include <Wt/WTable>
#include <Wt/WTimer>
#include <algorithm>
#include <unistd.h>
#include "TradePair.h"


using namespace Wt;
using namespace std;


class CryptoPiMain : public WApplication
{
public:
	CryptoPiMain(const WEnvironment& env);
	void addToMonitor();
	void updateTable();
	void resetTable();
	void updateVol();

private:
	WLineEdit *pairList_;
	WText *cryptoInfo_;
	WComboBox *interval_;
	WTable *table_;
	WTimer *timer_;
	vector<TradePair> pairs_;

	void greet();
};


CryptoPiMain::CryptoPiMain(const WEnvironment& env)
	: WApplication(env)
{
	setTitle("CryptoPi Main Menu");                               // application title

	root()->addWidget(new WText("Enter trade pair(s) that you would like to monitor, separated by comma (e.g. BTC-LTC,BTC-ETC): "));  // show some text

	root()->addWidget(new WBreak());                       // insert a line break

	pairList_ = new WLineEdit(root());                     // allow text input
	pairList_->setFocus();                                 // give focus

	root()->addWidget(new WText("\t every \t"));  // show some text
	interval_ = new WComboBox(root());
	interval_->addItem("30 sec");
	interval_->addItem("1 min");
	interval_->addItem("15 min");
	interval_->addItem("30 min");
	interval_->addItem("1 hour");

	root()->addWidget(new WBreak());                       // insert a line break
	root()->addWidget(new WBreak());                       // insert a line break

	WPushButton *button = new WPushButton("Start Monitoring", root());              // create a button
	button->setMargin(5, Left);                            // add 5 pixels margin

	root()->addWidget(new WBreak());                       // insert a line break
	root()->addWidget(new WBreak());                       // insert a line break

	cryptoInfo_ = new WText(root());                         // start with empty text

	root()->addWidget(new WBreak());                       // insert a line break

	table_ = new WTable(root());

	timer_ = new WTimer(root());
	timer_->timeout().connect(this, &CryptoPiMain::updateVol);

	// Bind the button push to the function
	button->clicked().connect(this, &CryptoPiMain::addToMonitor);

	// Bind to the Enter key when focused on the text to the function
	pairList_->enterPressed().connect(boost::bind(&CryptoPiMain::addToMonitor, this));
}

void CryptoPiMain::addToMonitor()
{
	timer_->stop();
	std::string t = pairList_->text().toUTF8();
	std::string newText;
	std::stringstream ss;

	pairs_.clear();
	std::string delimiter = ",";

	size_t pos = 0;
	std::string token;
	while ((pos = t.find(delimiter)) != std::string::npos) {
		token = t.substr(0, pos);
		pairs_.push_back(TradePair(token));
		t.erase(0, pos + delimiter.length());
	}
	pairs_.push_back(TradePair(t));

	ss << "You have chosen to monitor " << pairs_.size() << " pairs:";
	newText = ss.str();
	cryptoInfo_->setText(newText);

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

	timer_->setInterval(timeInterval*1000);
	timer_->start();

	CryptoPiMain::updateTable();
}

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
		std::string volume = std::to_string(pairs_[i].getVolume());
		std::string volumeChange = std::to_string(pairs_[i].fetchVolumeChange());
		std::string price = std::to_string(pairs_[i].getPrice());
		std::string priceChange = std::to_string(pairs_[i].fetchPriceChange());

		nameCell->addWidget(new WText(name));
		volCell->addWidget(new WText(volume));
		volChangeCell->addWidget(new WText(volumeChange));
		priceCell->addWidget(new WText(price));
		priceChangeCell->addWidget(new WText(priceChange));

	}
}

void CryptoPiMain::updateVol()
{
	int n = pairs_.size();
	for (int i = 0; i < n; i++){
		WTableCell *nameCell = table_->elementAt(i+1, 0);
		WTableCell *volCell = table_->elementAt(i+1, 1);
		WTableCell *volChangeCell = table_->elementAt(i+1, 2);
		WTableCell *priceCell = table_->elementAt(i+1, 3);
		WTableCell *priceChangeCell = table_->elementAt(i+1, 4);

		std::string name = pairs_[i].getName();
		std::string volumeChange = std::to_string(pairs_[i].fetchVolumeChange());
		std::string priceChange = std::to_string(pairs_[i].fetchPriceChange());

		pairs_[i].setVolume(pairs_[i].fetchVolume());
		std::string volume = std::to_string(pairs_[i].getVolume());
		std::string price = std::to_string(pairs_[i].getPrice());

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

WApplication *createApplication(const WEnvironment& env)
{

	return new CryptoPiMain(env);
}

int main(int argc, char **argv)
{
	return WRun(argc, argv, &createApplication);
}

