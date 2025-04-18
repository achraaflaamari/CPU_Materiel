//
// Created by achra on 11/11/2024.
//

#ifndef DATA_H
#define DATA_H
#include <bits/stdc++.h>
using namespace std;
struct Member {
    string nom;
    string prenom;
    string role;
    string refer;
    pair<string, string> rented = {"", ""};

    string serialize() const {
        return nom + "," + prenom + "," + role + "," + refer + "," + rented.first + "," + rented.second;
    }

    static Member deserialize(const string& data) {
        Member m;
        size_t pos = 0, prev_pos = 0;
        int count = 0;
        while ((pos = data.find(',', prev_pos)) != string::npos) {
            string part = data.substr(prev_pos, pos - prev_pos);
            switch (count) {
                case 0: m.nom = part; break;
                case 1: m.prenom = part; break;
                case 2: m.role = part; break;
                case 3: m.refer = part; break;
                case 4: m.rented.first = part; break;
            }
            prev_pos = pos + 1;
            count++;
        }
        m.rented.second = data.substr(prev_pos);
        return m;
    }
};
struct Component {
    string nom;
    string refer;
    int nombreTotal;
    mutable int nombreAlloue=0;
    string serialize() const {
        return nom + "," + refer + "," + to_string(nombreTotal) + "," + to_string(nombreAlloue)+",";
    }
    static Component deserialize(const string& data) {
        Component c;
        size_t pos = 0, prev_pos = 0;
        int count = 0;
        while ((pos = data.find(',', prev_pos)) != string::npos) {
            string part = data.substr(prev_pos, pos - prev_pos);
            switch (count) {
                case 0: c.nom = part; break;
                case 1: c.refer = part; break;
                case 2: c.nombreTotal = stoi(part); break;
                case 3: c.nombreAlloue = stoi(part); break;
            }
            prev_pos = pos + 1;
            count++;
        }
        return c;
    }
};
struct Allocation {
    string membreRefer;
    string composantRefer;
    string serialize() const {
        return membreRefer + "," + composantRefer +",";
    }
    static Allocation deserialize(const string& data) {
        Allocation alloc;
        size_t pos = 0, prev_pos = 0;
        int count = 0;
        while ((pos = data.find(',', prev_pos)) != string::npos) {
            string part = data.substr(prev_pos, pos - prev_pos);
            switch (count) {
                case 0: alloc.membreRefer = part; break;
                case 1: alloc.composantRefer = part; break;
            }
            prev_pos = pos + 1;
            count++;
        }
        return alloc;
    }
};

extern map<string, Allocation> allocations;
extern map<string, Component> components;
extern map<string, Member> members;

//gestion de membre
bool ajouter(Member& m);
bool modifierMembre(Member& m);
bool removeMemberByID(string& id);

//gestion de composant
bool ajouterComponent(const Component& comp);
bool updateComponentByReference(const Component& comp);
bool removeComponentByReference(const string& reference);

//gestion d'Allocation
bool allouerComposant(const string& membreRefer, const string& composantRefer);
bool retournerComposant(const string& membreRefer);


//Recherche Intelligent
vector<Member> recherche_Member_intelligent(const string& query);
vector<Component> recherche_Component_intelligent(const string& query);

//Enregistrement local
void loadComponentsFromFile(const string& filename);
void saveComponentsToFile(const string& filename);

void saveMembersToFile(const string& filename);
void loadMembersFromFile(const string& filename);

void loadAllocationsFromFile(const string& filename);
void saveAllocationsToFile(const string& filename);

#endif //DATA_H
