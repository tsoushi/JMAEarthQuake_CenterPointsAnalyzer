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

int main(void) {
	FILE *fp;
	char fname[] = "../data/h202003";
	char buf[97];

	fp = fopen(fname, "rb");
	if(fp == NULL) {
		printf("open file %s error", fname);
		return -1;
	}

	printf("start\n");

	int count = 0;
	struct record rec;
	std::map<std::string, int> ana;
	while(fread(buf, 1, 97, fp) != 0) {
		memcpy(&rec, &buf, 96);

		std::string key(rec.year, rec.year + 10);
		
		if(ana.find(key) == ana.end()) {
			ana[key] = 0;
		}
		ana[key]++;

	}

	for(auto itr = ana.begin(); itr != ana.end(); itr++) {
		printf("%s: %d\n", itr->first.c_str(), itr->second);
	}

	fclose(fp);

	return 0;
}
