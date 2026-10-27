#include <stdio.h>
#include <string.h>

#define MAX_RECORDS 100

typedef struct {
    char  stationId[10];
    char  date[11];          /* DD-MM-YYYY */
    float pm25, pm10, no2, so2;
    int   aqi;
} Reading;

Reading records[MAX_RECORDS];
int count = 0;

/* Returns 1 if all pollutant values lie in a valid range */
int isValid(float pm25, float pm10, float no2, float so2) {
    return pm25 >= 0 && pm25 <= 500 && pm10 >= 0 && pm10 <= 600 &&
           no2  >= 0 && no2  <= 400 && so2  >= 0 && so2  <= 400;
}

/* Returns 1 if the station-date pair already exists */
int isDuplicate(const char *id, const char *date) {
    for (int i = 0; i < count; i++)
        if (strcmp(records[i].stationId, id) == 0 &&
            strcmp(records[i].date, date) == 0)
            return 1;
    return 0;
}

int addReading(void) {
    Reading r;
    if (count >= MAX_RECORDS) { printf("Storage full.\n"); return 0; }

    printf("Station ID: ");        scanf("%9s",  r.stationId);
    printf("Date (DD-MM-YYYY): "); scanf("%10s", r.date);
    if (isDuplicate(r.stationId, r.date)) {
        printf("Duplicate record.\n");
        return 0;
    }

    printf("PM2.5 PM10 NO2 SO2: ");
    while (scanf("%f %f %f %f", &r.pm25, &r.pm10, &r.no2, &r.so2) != 4
           || !isValid(r.pm25, r.pm10, r.no2, r.so2)) {
        while (getchar() != '\n');          /* clear input buffer */
        printf("Invalid values. Re-enter: ");
    }

    r.aqi = 0;                              /* calculated in Module 4 */
    records[count++] = r;
    printf("Record saved.\n");
    return 1;
}

int main(void) {
    addReading();
    addReading();
    addReading();
    return 0;
}
