#include <bits/stdc++.h>
#include "DATA.h"
using namespace std;


map<string, Member> members;
map<string, Component> components;
map<string, Allocation> allocations;

// Gestion de Membre
bool ajouter(Member& m) {
    if(members.count(m.refer) == 1)
        return false;
    members[m.refer] = m;
    return true;
}
bool modifierMembre(Member& m) {
    if(members.count(m.refer) == 0)
        return false;
    members[m.refer] = m;
    return true;
}
bool removeMemberByID(string& id) {
    if (members.erase(id)) {
        return true;
    }
    return false;
}

//Gestion de composant
bool ajouterComponent(const Component& comp) {
    comp.nombreAlloue=0;
    components[comp.refer] = comp;
    return true;
}
bool updateComponentByReference(const Component& comp) {
    if (components.count(comp.refer)==0) {
        return false;
    }
    components[comp.refer] = comp;
    return true;

}
bool removeComponentByReference(const string& reference) {
    if (components.count(reference)==1) {
        components.erase(reference);
        return true;
    }
    return false;
}

//gestion d'Allocation
bool allouerComposant(const string& membreRefer, const string& composantRefer) {
    if (allocations.count(membreRefer) == 1||members.count(membreRefer) == 0||components.count(composantRefer) == 0
        ||components[composantRefer].nombreTotal==components[composantRefer].nombreAlloue) {
        return false;
    }
    for (const auto& pair : allocations) {
        if (pair.second.composantRefer == composantRefer) {
            return false;
        }
    }


    Allocation alloc = { membreRefer, composantRefer};
    allocations[membreRefer] = alloc;
    (components[composantRefer].nombreAlloue)+=1;

    members[membreRefer].rented.first=components[composantRefer].nom;
    members[membreRefer].rented.second=composantRefer;

    return true;
}
bool retournerComposant(const string& membreRefer) {
    if (allocations.count(membreRefer) == 1) {
        (components[allocations[membreRefer].composantRefer].nombreAlloue)-=1;
        members[membreRefer].rented.first="";
        members[membreRefer].rented.second="";



        allocations.erase(membreRefer);
        return true;
    }
    return false;
}

//Recherche Intelligent
vector<Member> recherche_Member_intelligent(const string& query) {
    vector<Member> vect;
    if(query.empty()) {
        for (const auto& pair : members) {
            vect.push_back(pair.second);
        }
        return vect;
    }

    for (const auto& pair : members) {
        const Member& m = pair.second;

        string nomLower = m.nom, prenomLower = m.prenom,
        referLower = m.refer,roleLower = m.role,
        compLower = m.rented.second
        ,
        queryLower = query;

        transform(nomLower.begin(), nomLower.end(), nomLower.begin(), ::tolower);
        transform(prenomLower.begin(), prenomLower.end(), prenomLower.begin(), ::tolower);
        transform(referLower.begin(), referLower.end(), referLower.begin(), ::tolower);
        transform(roleLower.begin(), roleLower.end(), roleLower.begin(), ::tolower);
        transform(compLower.begin(), compLower.end(), compLower.begin(), ::tolower);
        transform(queryLower.begin(), queryLower.end(), queryLower.begin(), ::tolower);

        // Vérification de la présence de la requête dans chaque champ
        if (nomLower.find(queryLower) != string::npos ||
            prenomLower.find(queryLower) != string::npos ||
            roleLower.find(queryLower) != string::npos ||
            compLower.find(queryLower) != string::npos ||
            referLower.find(queryLower) != string::npos) {
            vect.push_back(m);
        }
    }
    return vect;
}
vector<Component> recherche_Component_intelligent(const string& query) {
    vector<Component> vect;
    if(query.empty()) {
        for (const auto& comp : components) {
            vect.push_back(comp.second);
        }
        return vect;
    }

    for (const auto& comp : components) {
        string nomLower = comp.second.nom, referLower = comp.second.refer,
        nbtotalLower = std::to_string(comp.second.nombreTotal), nballLower = std::to_string(comp.second.nombreAlloue)
        , queryLower = query;
        transform(nomLower.begin(), nomLower.end(), nomLower.begin(), ::tolower);
        transform(referLower.begin(), referLower.end(), referLower.begin(), ::tolower);
        transform(nbtotalLower.begin(), nbtotalLower.end(), nbtotalLower.begin(), ::tolower);
        transform(nballLower.begin(), nballLower.end(), nballLower.begin(), ::tolower);
        transform(queryLower.begin(), queryLower.end(), queryLower.begin(), ::tolower);

        // Vérification de la présence de la requête dans chaque champ
        if (nomLower.find(queryLower) != string::npos ||
            nbtotalLower.find(queryLower) != string::npos ||
            nballLower.find(queryLower) != string::npos ||
            referLower.find(queryLower) != string::npos) {
            vect.push_back(comp.second);
        }
    }
    return vect;
}


//Enregistrement local
void loadComponentsFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        components.clear();
        while (getline(file, line)) {
            Component c = Component::deserialize(line);
            components[c.refer] = c;
        }
        file.close();
    }
}
void saveComponentsToFile(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (auto it = components.begin(); it != components.end(); ++it) {
            file << it->second.serialize() << endl; // Sérialisation du composant
        }
        file.close();
    }
}

void saveMembersToFile(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (auto it = members.begin(); it != members.end(); ++it) {
            file << it->second.serialize() << endl;
        }
        file.close();
    }
}
void loadMembersFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        members.clear();
        while (getline(file, line)) {
            Member m = Member::deserialize(line);
            members[m.refer] = m;
        }
        file.close();
    }
}

void loadAllocationsFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        allocations.clear();
        while (getline(file, line)) {
            Allocation alloc = Allocation::deserialize(line);
            allocations[alloc.membreRefer] = alloc;
        }
        file.close();
    }
}
void saveAllocationsToFile(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (auto& pair : allocations) {
            file << pair.second.serialize() << endl;
        }
        file.close();
    }
}