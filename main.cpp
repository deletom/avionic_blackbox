//-----------------------------
//----- INCLUDE 	  -----
//-----------------------------
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <string>
#include <vector>
#include <ctime>

#include "Redis.h"

//-----------------------------
//----- DEFINE 		  -----
//-----------------------------

#define PATH_LOG_IMU_SENSEHAT "/home/pi/log/sensehat.log"
#define PATH_LOG_IMU_GPS "/home/pi/log/gps.log"
#define PATH_LOG_IMU_LINK "/home/pi/log/link.log"

//-----------------------------
//----- Namespace 	  -----
//-----------------------------
using namespace std;

//-----------------------------
//----- Fonction Main	  -----
//-----------------------------

int main(int argc, char** argv) {

    Redis objRedis;

    // Ouverture des différents fichiers de log
    ofstream fileImuSenseHat(PATH_LOG_IMU_SENSEHAT, ios::out | ios::trunc);
    ofstream fileImuGps(PATH_LOG_IMU_GPS, ios::out | ios::trunc);
    ofstream fileImuLink(PATH_LOG_IMU_LINK, ios::out | ios::trunc);

    // Erreur à l'ouverture
    if (fileImuSenseHat != true) {
        cout << "Erreur Fichier SenseHat";
    }
    if (fileImuGps != true) {
        cout << "Erreur Fichier Gps";
    }
    if (fileImuLink != true) {
        cout << "Erreur Fichier Link";
    }

    while (true) {
        time_t now = time(0);
        char* dt = ctime(&now);

        if (fileImuSenseHat) {
            fileImuSenseHat << dt << " OFFSET   " << objRedis.getDataSimple("offset_x") << ";" << objRedis.getDataSimple("offset_y") << ";" << objRedis.getDataSimple("offset_z") << ";" << objRedis.getDataSimple("offset_altitude") << endl;
            fileImuSenseHat << dt << " RAW ATT  " << objRedis.getDataSimple("current_raw_x") << ";" << objRedis.getDataSimple("current_raw_y") << ";" << objRedis.getDataSimple("current_raw_z") << ";" << objRedis.getDataSimple("current_raw_altitude") << endl;
            fileImuSenseHat << dt << " RAW ACC  " << objRedis.getDataSimple("current_accel_x") << ";" << objRedis.getDataSimple("current_accel_y") << ";" << objRedis.getDataSimple("current_accel_z") << endl;
            fileImuSenseHat << dt << " COMP ATT " << objRedis.getDataSimple("current_compensated_x") << ";" << objRedis.getDataSimple("current_compensated_y") << ";" << objRedis.getDataSimple("current_compensated_z") << ";" << objRedis.getDataSimple("current_compensated_altitude") << endl;
            fileImuSenseHat << dt << " STATUS   " << objRedis.getDataSimple("current_time_imu") << endl;
            fileImuSenseHat << dt << endl;
        }
        
        if (fileImuGps) {
            fileImuGps << dt << " BASE     " << objRedis.getDataSimple("base_Latitude") << ";" << objRedis.getDataSimple("base_Latitude_Indicator") << ";" << objRedis.getDataSimple("base_Longitude") << ";" << objRedis.getDataSimple("base_Longitude_Indicator") << endl;
            fileImuGps << dt << " CURR     " << objRedis.getDataSimple("current_Latitude") << ";" << objRedis.getDataSimple("current_Latitude_Indicator") << ";" << objRedis.getDataSimple("current_Longitude") << ";" << objRedis.getDataSimple("current_Longitude_Indicator") << endl;
            fileImuGps << dt << " STATUS   " << objRedis.getDataSimple("current_GPS_Status") << ";" << objRedis.getDataSimple("current_time_gps") << endl;
            fileImuGps << dt << endl;
        }
        
        if (fileImuLink) {
            
        }

        usleep(1000000);
    }

    if (fileImuSenseHat) {
        fileImuSenseHat.close();
    }
    if (fileImuGps) {
        fileImuGps.close();
    }
    if (fileImuLink) {
        fileImuLink.close();
    }

    return EXIT_SUCCESS;
}