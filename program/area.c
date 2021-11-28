#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <unistd.h>

struct Record {
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


float getLat(char *data){
	char lat_deg[4];
	char lat_min[5];
	float lat;

	memcpy(lat_deg, data+21, 3);
	lat_deg[3] = '\0';

	memcpy(lat_min, data+24, 4);
	if(lat_min[2] == ' '){lat_min[2] = '0';}
	if(lat_min[3] == ' '){lat_min[3] = '0';}
	lat_min[4] = '\0';

	lat = atoi(lat_deg);
	lat += (atof(lat_min)/100/60) * (lat >= 0 ? 1 : -1);
	return lat;
}

float getLon(char *data){
	char lon_deg[5];
	char lon_min[5];
	float lon;

	memcpy(lon_deg, data+32, 4);
	lon_deg[4] = '\0';

	memcpy(lon_min, data+36, 4);
	if(lon_min[2] == ' '){lon_min[2] = '0';}
	if(lon_min[3] == ' '){lon_min[3] = '0';}
	lon_min[4] = '\0';

	lon = atoi(lon_deg);
	lon += (atof(lon_min)/100/60) * (lon >= 0 ? 1 : -1);
	return lon;
}

// 使い方
//
// cmd 基準緯度[float]　基準経度[float]　許容緯度差[float]　許容経度差[float]
int main(int argc, char const *argv[]) {
	FILE *fp;
	char buf[97];
	char filename[128];
	struct Record record;

	float baseLatitude = atof(argv[1]);
	float baseLongitude = atof(argv[2]);
	float latRange = atof(argv[3]);
	float lonRange = atof(argv[4]);

	for(int i = 1919; i<=2019; i++){
		snprintf(filename, 128, "../data/h%d", i);
		fp = fopen(filename, "rb");
		if(fp == NULL) {
			continue;
		}

		float lat, lon, lat_dif, lon_dif;
		while(fread(buf, 1, 97, fp) != 0){

			lat = getLat(buf);
			lon = getLon(buf);

			lat_dif = lat - baseLatitude;
			if(-latRange <= lat_dif && lat_dif <= latRange){
				lon_dif = lon - baseLongitude;
				if(-lonRange <= lon_dif && lon_dif <= lonRange){
					memcpy(&record, buf, 96);
					printf("%.4s/%.2s/%.2s I%c M%.2s %f/%f %.24s\n",
						record.year, record.month, record.day,
						record.maxIntensity, record.magnitude1,
						lat, lon,
						record.centerName);
				}
			}

		}

		fclose(fp);
	}


	return 0;
}

