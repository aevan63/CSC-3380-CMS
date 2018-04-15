//Written by Jackie Bowers

#include "BuildHTML.h"
#include <iostream>

using namespace std;
BuildHTML::BuildHTML(const Fastcgipp::Http::Environment& environment()) {
	string line;
	ifstream file;
	file.open(uri);
	if (file.is_open()) {
		while(getline(file,line)) {
			html << line;
		}
	}

}

BuildHTML::BuildHTML(MYSQL_ROW* RES, const Fastcgipp::Http::Environment& environment(), std::string website) {
	this->website =  website+"(.*)";
	uri = tr1::regex_replace(environment().requestUri,this->website,"");
	string line;
	ifstream file;
	file.open(uri);
	if (file.is_open()) {
		while(getline(file,line)) {
			html << line;
		}
	}
	stringRES = new string(sizeof(RES));
	for (int i = 0; i<sizeof(RES);++i) {
		stringRES[i] = RES[i];
	}
}
string* BuildHTML::buildFromSQL() {
	//code goes here
	//will likely use Christian's feedback classes here I think
	return stringRES;
}

string BuildHTML::fixHTML(string* HTMLRes) {
	tr1::regex tempR;
	std::basic_string tempS;
	for (int i = 0;i<sizeof(parameters);++i) {
		tempR(uri);
		if (tr1::regex_match(parameters[i], tempR)) {
			++i;
			tempR("(locator = )(.*)");
			if(regex_match(parameters[i],tempR)) {
				tempS = parameters[i];
				tr1::regex_replace(tempS,tempR,"");
				break;
			}
		}
	}
	tr1::regex locator(tempS);
	//obviously needs to be more complicated than just using the first row of the returned values
	tr1::regex_replace(html,locator,HTMLRes[0]);
	return html;
}

string BuildHTML::getHtml() {
	return html;
}

string BuildHTML::geturi() {
	return uri;
}

