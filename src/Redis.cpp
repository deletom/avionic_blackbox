/**
 * Get Object Redis connexion
 */
#include "Redis.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>


using namespace std;
using namespace redis3m;
using namespace boost;


#define PREFIX "config_"
#define FILE_CONFIG "./config.ini"

Redis::Redis() {
    m_conn = connection::create();
}

bool Redis::setDataList(std::string key, vector<std::string> data) {
    m_conn->run(command("LPUSH") << key << boost::algorithm::join(data, "|"));

    return true;
}

bool Redis::setDataSimple(std::string key, std::string data) {
    m_conn->run(command("SET") << key << data);

    return true;
}

std::string Redis::getDataSimple(std::string key) {
    reply r = m_conn->run(command("GET") << key);
    return r.str();
}

void Redis::setDataConfig() {

    m_conn->run(command("FLUSHALL"));
    
    /*
     * On traite le fichier de configuration pour ajouter les éléments sous redis
     */
    // Ouverture du fichier ini
    ifstream fichier(FILE_CONFIG, ios::in);

    if (fichier) // si l'ouverture a réussi
    {
        // Contenu de la ligne en cours
        string line;
        // Contenu de la section en cours
        string currentPrefixKey = "";

        // On scrute l'ensemble du fichier
        while (getline(fichier, line)) {

            // On cherche une section
            std::size_t firstSection = line.find("[");
            std::size_t lastSection = line.find("]");

            vector<string> strs;

            // On teste si on trouve un nom de section
            if (firstSection != std::string::npos && lastSection != std::string::npos) {
                currentPrefixKey = PREFIX + line.substr(1, line.find("]") - 1);

            } else {
                // Sinon, c'est une valeur de paramétrage
                boost::split(strs, line, boost::is_any_of("="));

                if (strs.size() == 2) {
                    string key;
                    key = currentPrefixKey + "_" + strs[0];
                    Redis::setDataSimple(key, strs[1]);
                }
            }
        }

        fichier.close(); // on ferme le fichier
    } else {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    }

    // On initialise un vol, pour l'instant, nous le lançons en dur.
    // A terme, la station sol s'en occupera
    Redis::setDataSimple("current_flight_inprogress", "1");
}
