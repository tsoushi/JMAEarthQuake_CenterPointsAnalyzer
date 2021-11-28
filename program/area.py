import os
import time

def getLat(rec):
    try:
        return int(rec[21:24]) + int(rec[24:28].replace(b' ', b'0'))/100/60
    except Exception:
        return 0

def getLon(rec):
    try:
        return int(rec[32:36]) + int(rec[36:40].replace(b' ', b'0'))/100/60
    except Exception:
        return 0

def main():
    baseLat = 38.1
    baseLon = 142.85
    latRange = 0.1
    lonRange = 0.1

    files = ['data'+os.sep+i for i in os.listdir('data')]

    for file in files:
        f = open(file, 'rb')
        while 1:
            rec = f.readline()

            lat = getLat(rec)
            lon = getLon(rec)

            
            if abs(lat - baseLat) <= latRange:
                if abs(lon - baseLon) <= lonRange:
                    print(rec[1:9], lat, lon, abs(lat - baseLat), abs(lon - baseLon))

            if not rec:
                break


if __name__ == '__main__':
    main()

