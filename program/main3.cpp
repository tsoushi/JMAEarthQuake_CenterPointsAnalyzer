#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <string>

#include <map>


struct record {
	char header;
	char year[4];
	char month[2];
	char day[2];
	char hour[2];
	char minute[2];
	char second[4];
	char second_error[4];
	char latitude[3];
	char latitude_minute[4];
	char latitude_minute_error[4];
	char longitude[4];
	char longitude_minute[4];
	char longitude_minute_error[4];
	char depth[5];
	char depth_error[3];
	char magnitude1[2];
	char magnitude1_info;
	char magnitude2[2];
	char magnitude2_info;
	char travelTime;
	char hypocenter_eval;
	char hypocenter_eval_add;
	char maxIntensity;
	char damage_scale;
	char wave_scale;
	char centerNum_large;
	char centerNum_small[3];
	char centerName[24];
	char nObserver[3];
	char determineFlag;
};

int analyze(std::map<std::string, int> *ana, std::string fname) {
	FILE *fp;
	char buf[97];


	fp = fopen(fname.c_str(), "rb");
	if(fp == NULL) {
		return -1;
	}

	printf("loading file : %s\n", fname.c_str());

	int count = 0;
	struct record rec;
	while(fread(buf, 1, 97, fp) != 0) {
		memcpy(&rec, &buf, 96);

		std::string key(rec.magnitude1, rec.magnitude1 + 2);
		
		if((*ana).find(key) == (*ana).end()) {
			(*ana)[key] = 0;
		}
		(*ana)[key]++;

	}

	fclose(fp);

	return 0;
}

int main(void) {
	std::map<std::string, int> ana;

	for(int i = 1919; i<=2019; i++){
		analyze(&ana, "../data/h"+std::to_string(i));
	}

	analyze(&ana, "h202001");
	analyze(&ana, "h202002");
	analyze(&ana, "h202003");

	for(auto itr = ana.begin(); itr != ana.end(); itr++) {
		printf("%s: %d\n", itr->first.c_str(), itr->second);
	}
	return 0;
}

