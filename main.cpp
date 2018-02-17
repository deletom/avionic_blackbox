/**
 * Module de suivi des executions de l'avionique
 * Auteur : Thomas DELECOURT
 */

//-----------------------------
//----- INCLUDE 	  -----
//-----------------------------
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <thread>
#include <string>
#include <vector>
#include <ctime>

#include "Redis.h"

//-----------------------------
//----- DEFINE 		  -----
//-----------------------------

#define PATH_LOG_IMU_SENSEHAT   "/home/pi/log/sensehat.log"
#define PATH_LOG_IMU_GPS        "/home/pi/log/gps.log"
#define PATH_LOG_IMU_LINK       "/home/pi/log/link.log"
#define PATH_LOG_THREAD         "/home/pi/log/thread.log"

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
    ofstream fileThread(PATH_LOG_THREAD, ios::out | ios::trunc);

    // Erreur à l'ouverture
    if (!fileImuSenseHat.is_open()) {
        cout << "Erreur Fichier SenseHat";
    }
    if (!fileImuGps.is_open()) {
        cout << "Erreur Fichier Gps";
    }
    if (!fileImuLink.is_open()) {
        cout << "Erreur Fichier Link";
    }
    if (!fileThread.is_open()) {
        cout << "Erreur Fichier Thread";
    }

    while (true) {

        // Récupération d'un temps unique
        char dt[10];
        time_t t;
        struct tm *tmp;

        t = time(NULL);
        tmp = localtime(&t);
        strftime(dt, 10, "%H %M %S ", tmp);

        if (fileImuSenseHat.is_open()) {
            fileImuSenseHat << dt << " OFFSET   " << objRedis.getDataSimple("offset_x") << ";" << objRedis.getDataSimple("offset_y") << ";" << objRedis.getDataSimple("offset_z") << ";" << objRedis.getDataSimple("offset_altitude") << endl;
            fileImuSenseHat << dt << " RAW ATT  " << objRedis.getDataSimple("current_raw_x") << ";" << objRedis.getDataSimple("current_raw_y") << ";" << objRedis.getDataSimple("current_raw_z") << ";" << objRedis.getDataSimple("current_raw_altitude") << endl;
            fileImuSenseHat << dt << " RAW ACC  " << objRedis.getDataSimple("current_accel_x") << ";" << objRedis.getDataSimple("current_accel_y") << ";" << objRedis.getDataSimple("current_accel_z") << endl;
            fileImuSenseHat << dt << " COMP ATT " << objRedis.getDataSimple("current_compensated_x") << ";" << objRedis.getDataSimple("current_compensated_y") << ";" << objRedis.getDataSimple("current_compensated_z") << ";" << objRedis.getDataSimple("current_compensated_altitude") << endl;
            fileImuSenseHat << dt << " STATUS   " << objRedis.getDataSimple("current_time_imu") << endl;
            fileImuSenseHat << dt << endl;
        }

        if (fileImuGps.is_open()) {
            fileImuGps << dt << " BASE     " << objRedis.getDataSimple("base_Latitude") << ";" << objRedis.getDataSimple("base_Latitude_Indicator") << ";" << objRedis.getDataSimple("base_Longitude") << ";" << objRedis.getDataSimple("base_Longitude_Indicator") << endl;
            fileImuGps << dt << " CURR     " << objRedis.getDataSimple("current_Latitude") << ";" << objRedis.getDataSimple("current_Latitude_Indicator") << ";" << objRedis.getDataSimple("current_Longitude") << ";" << objRedis.getDataSimple("current_Longitude_Indicator") << endl;
            fileImuGps << dt << " STATUS   " << objRedis.getDataSimple("current_GPS_Status") << ";" << objRedis.getDataSimple("current_time_gps") << endl;
            fileImuGps << dt << endl;
        }

        if (fileImuLink.is_open()) {

        }

        if (fileThread.is_open()) {
            fileThread << dt << " DIAG   " << objRedis.getDataSimple("proc_diag") << endl;
            fileThread << dt << " IMU    " << objRedis.getDataSimple("proc_imu") << endl;
            fileThread << dt << " LINK   " << objRedis.getDataSimple("proc_link") << endl;
        }

        usleep(1000000);
    }

    if (fileImuSenseHat.is_open()) {
        fileImuSenseHat.close();
    }
    if (fileImuGps.is_open()) {
        fileImuGps.close();
    }
    if (fileImuLink.is_open()) {
        fileImuLink.close();
    }
    if (fileThread.is_open()) {
        fileThread.close();
    }

    return EXIT_SUCCESS;
}