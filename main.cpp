
#include <QMovie>
#include <QMessageBox>
#include<QStandardItemModel>
#include <QScreen>
#include <qstyle.h>
#include<QTimer>
#include<QStyleFactory>
#include <bits/stdc++.h>
#include "DATA.h"

#include "cmake-build-debug/ui_CPU.h"
using namespace std;

void initMenu(Ui::MainWindow ui) {
    ui.menu->setHidden(true);
    QObject::connect(ui.Menushow, &QPushButton::clicked, [ui]() {
        if(ui.menu->isHidden()) {
            ui.menu->setHidden(false);
        }else
            ui.menu->setHidden(true);
    });
    QObject::connect(ui.HOMEB, &QPushButton::clicked, [ui]() {
        ui.stackedWidget->setCurrentWidget(ui.HOME);
    });

    QObject::connect(ui.Member, &QPushButton::clicked, [ui]() {
        ui.menu->setCurrentWidget(ui.MenuMembre);
        ui.menu->setHidden(false);
    });
    QObject::connect(ui.Composant, &QPushButton::clicked, [ui]() {
        ui.menu->setCurrentWidget(ui.MenuComp);
        ui.menu->setHidden(false);
    });
    QObject::connect(ui.Recherche, &QPushButton::clicked, [ui]() {
        ui.menu->setCurrentWidget(ui.MenuRecherche);
        ui.menu->setHidden(false);
    });
}

void updatedateC(const Ui::MainWindow & ui) {
    QTableView *table = ui.Ctable;
    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderLabels({"NOM", "REFERENCE","NOMBRE TOTAL","NOMBRE ALLOUE"});
    QLineEdit* refere = ui.CRecherche;
    refere->clear();
    unsigned int i=0;
    for(Component comp:recherche_Component_intelligent("")) {
        model->setItem(i, 0, new QStandardItem(comp.nom.data()));
        model->setItem(i, 1, new QStandardItem(comp.refer.data()));
        model->setItem(i, 2, new QStandardItem(std::to_string(comp.nombreTotal).data()));
        model->setItem(i, 3, new QStandardItem(std::to_string(comp.nombreAlloue).data()));i++;
    }
    table->setModel(model);
}
void updatedateM(const Ui::MainWindow & ui) {
    QTableView *table = ui.Mtable;
    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderLabels({"cin","nom", "prenom","role","composantID"});
    QLineEdit* refere = ui.MRecherche;
    refere->clear();
    unsigned int i=0;
    for(Member m :recherche_Member_intelligent("")) {
        model->setItem(i, 0, new QStandardItem(m.refer.data()));
        model->setItem(i, 1, new QStandardItem(m.nom.data()));
        model->setItem(i, 2, new QStandardItem(m.prenom.data()));
        model->setItem(i, 3, new QStandardItem(m.role.data()));
        model->setItem(i, 4, new QStandardItem(m.rented.second.data()));
        i++;
    }
    table->setModel(model);
}


void pageButton(QPushButton * bt,QWidget * page,Ui::MainWindow ui) {
    QObject::connect(bt, &QPushButton::clicked, [ui,page]() {
        if(page==ui.PageRechercheMembre) {
            updatedateM(ui);
        }
        if(page==ui.PageRechercheComposant) {
            updatedateC(ui);
        }
        ui.stackedWidget->setCurrentWidget(page);
    });
}
void FonctionAjouterMembre(Ui::MainWindow ui) {
    QObject::connect(ui.AMajouter, &QPushButton::clicked, [ui]() {
        QLineEdit* refer = ui.AMcin;
        QLineEdit* nom = ui.AMnom;
        QLineEdit* prenom = ui.AMprenom;
        QLineEdit* role = ui.AMrole;
        Member m ={(nom->text()).toStdString(),(prenom->text()).toStdString()
            ,(role->text()).toStdString(),(refer->text()).toStdString()};
        if(ajouter(m)) {
            QMessageBox::information(ui.FormAjoutMember, "Succès", "Membre ajouté avec Succès");
            refer->clear();
            nom->clear();
            prenom->clear();
            role->clear();
        }else
            QMessageBox::critical(ui.FormAjoutMember, "Erreur", "Ajout de membre est impossible");
    });
}
void FonctionModifierMembre(Ui::MainWindow ui) {
    QObject::connect(ui.MMmodifier, &QPushButton::clicked, [ui]() {
        QLineEdit* refer = ui.MMcin;
        QLineEdit* nom = ui.MMnom;
        QLineEdit* prenom = ui.MMprenom;
        QLineEdit* role = ui.MMrole;
        Member m ={(nom->text()).toStdString(),(prenom->text()).toStdString()
            ,(role->text()).toStdString(),(refer->text()).toStdString()};
        if(modifierMembre(m)) {
            QMessageBox::information(nullptr, "Succès", "Modification  effectué");
            refer->clear();
            nom->clear();
            prenom->clear();
            role->clear();
        }else
            QMessageBox::critical(nullptr, "Erreur", "Membre est inexistant !!");
    });
}
void FonctionSupprimerMembre(Ui::MainWindow ui) {
    QObject::connect(ui.SMsupprimer, &QPushButton::clicked, [ui]() {
        QLineEdit* refer = ui.SMmembre;
        string s =refer->text().toStdString();
        if (removeMemberByID(s)){
            QMessageBox::information(nullptr, "Succès", "Suppression  effectué");
            refer->clear();
        }else
            QMessageBox::critical(nullptr, "Erreur", "Membre est inexistant !!");
    });
}


void FonctionAjouterComposant(const Ui::MainWindow & ui) {
    QObject::connect(ui.ACajouter, &QPushButton::clicked, [ui]() {
        QLineEdit* refer = ui.ACreference;
        QLineEdit* nom = ui.ACnom;
        QLineEdit* nbtotal = ui.ACnbre;
        Component comp ={(nom->text()).toStdString(),(refer->text()).toStdString()
            ,stoi((nbtotal->text()).toStdString())};
        if(ajouterComponent(comp)) {
            QMessageBox::information(nullptr, "Succès", "Composant ajouté avec Succès");
            refer->clear();
            nom->clear();
            nbtotal->clear();
        }else
            QMessageBox::critical(nullptr, "Erreur", "Ajout de Composant est impossible");
    });
}
void FonctionModifierComposant(const Ui::MainWindow & ui) {
    QObject::connect(ui.MCmodifier, &QPushButton::clicked, [ui]() {
        QLineEdit* refer = ui.MCrefer;
        QLineEdit* nom = ui.MCnom;
        QLineEdit* nbtotal = ui.MCnbre;
        Component comp ={(nom->text()).toStdString(),(refer->text()).toStdString()
            ,stoi((nbtotal->text()).toStdString())};
        if(updateComponentByReference(comp)) {
            QMessageBox::information(nullptr, "Succès", "Modification  effectué");
            refer->clear();
            nom->clear();
            nbtotal->clear();
        }else
            QMessageBox::critical(nullptr, "Erreur", "Modification est impossible");
    });
}
void FonctionSupprimerComposant(const Ui::MainWindow & ui) {
    QObject::connect(ui.SCsupprimer, &QPushButton::clicked, [ui]() {
        QLineEdit* refer = ui.SCrefer;
        string s =refer->text().toStdString();
        if (removeComponentByReference(s)){
            QMessageBox::information(nullptr, "Succès", "Suppression  effectué");
            refer->clear();
        }else
            QMessageBox::critical(nullptr, "Erreur", "Composant est inexistant !!");
    });
}
void FonctionAllouerComposant(const Ui::MainWindow & ui) {
    QObject::connect(ui.ALCallouer, &QPushButton::clicked, [ui]() {
        QLineEdit* refermm = ui.ALCcin;
        QLineEdit* refercm = ui.ALCrefer;
        string member =refermm->text().toStdString();
        string comp =refercm->text().toStdString();
        if (allouerComposant(member,comp)){
            QMessageBox::information(nullptr, "Succès", "Allocation  effectué");
            refermm->clear();
            refercm->clear();
        }else
            QMessageBox::critical(nullptr, "Erreur", "Allocation est Impossible !!!");
    });
}
void FonctionRetournerComposant(const Ui::MainWindow & ui) {
    QObject::connect(ui.RCretour, &QPushButton::clicked, [ui]() {
        QLineEdit* refer = ui.RCrefer;
        string s =refer->text().toStdString();
        if (retournerComposant(s)){
            QMessageBox::information(nullptr, "Succès", "Retour de composant effectué");
            refer->clear();
        }else
            QMessageBox::critical(nullptr, "Erreur", "Erreur d'operation !!");
    });
}

void FonctionRechercheMembre(const Ui::MainWindow & ui) {
    QTableView *table = ui.Mtable;
    QObject::connect(ui.MRecherche, &QLineEdit::textChanged, [ui,table]() {
        QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderLabels({"cin","nom", "prenom","role","composantID"});
        QLineEdit* refere = ui.MRecherche;
        string s =refere->text().toStdString();
        unsigned int i=0;
        for(Member m :recherche_Member_intelligent(s)) {
            model->setItem(i, 0, new QStandardItem(m.refer.data()));
            model->setItem(i, 1, new QStandardItem(m.nom.data()));
            model->setItem(i, 2, new QStandardItem(m.prenom.data()));
            model->setItem(i, 3, new QStandardItem(m.role.data()));
            model->setItem(i, 4, new QStandardItem(m.rented.second.data()));
            i++;
        }
        table->setModel(model);
    });

}
void FonctionRechercheComposant(const Ui::MainWindow & ui) {
    QTableView *table = ui.Ctable;
    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderLabels({"NOM", "REFERENCE","NOMBRE TOTAL","NOMBRE ALLOUE"});
    int i=0;
    for(Component comp:recherche_Component_intelligent("")) {
        model->setItem(i, 0, new QStandardItem(comp.nom.data()));
        model->setItem(i, 1, new QStandardItem(comp.refer.data()));
        model->setItem(i, 2, new QStandardItem(std::to_string(comp.nombreTotal).data()));
        model->setItem(i, 3, new QStandardItem(std::to_string(comp.nombreAlloue).data()));
        i++;
    }
    table->setModel(model);



    QObject::connect(ui.CRecherche, &QLineEdit::textChanged, [ui,table]() {
        QStandardItemModel *model = new QStandardItemModel();
        model->setHorizontalHeaderLabels({"NOM", "REFERENCE","NOMBRE TOTAL","NOMBRE ALLOUE"});
        QLineEdit* refere = ui.CRecherche;
        string s =refere->text().toStdString();
        unsigned int i=0;
        for(Component comp:recherche_Component_intelligent(s)) {
            model->setItem(i, 0, new QStandardItem(comp.nom.data()));
            model->setItem(i, 1, new QStandardItem(comp.refer.data()));
            model->setItem(i, 2, new QStandardItem(std::to_string(comp.nombreTotal).data()));
            model->setItem(i, 3, new QStandardItem(std::to_string(comp.nombreAlloue).data()));
        i++;
    }
        table->setModel(model);
    });

}

void closing() {
    saveAllocationsToFile("allocations.txt");
    saveMembersToFile("members.txt");
    saveComponentsToFile("components.txt");
}
int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    QLabel label;

    QMovie *movie = new QMovie("CPU.gif");
    label.setMovie(movie);
    label.setWindowFlags(Qt::FramelessWindowHint);
    movie->start();

    // Ajuster la taille de la fenêtre pour s'adapter au GIF
    label.resize(movie->currentImage().size());

    // Obtenir la géométrie de l'écran principal et calculer la position centrée
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - label.width()) / 2;
    int y = (screenGeometry.height() - label.height()) / 2;
    label.move(x, y);

    QMainWindow window;
    Ui::MainWindow ui;
    ui.setupUi(&window);
    initMenu(ui);

    pageButton(ui.AjouterMember,ui.PageAjouterMember,ui);
    pageButton(ui.ModifierMember,ui.PageModifierMembre,ui);
    pageButton(ui.SupprimerMember,ui.PageSupprimerMembre,ui);


    pageButton(ui.AjouterComposant,ui.PageAjoutComposant,ui);
    pageButton(ui.ModifierComposant,ui.PageModifierComposant,ui);
    pageButton(ui.SupprimerComposant,ui.PageSupprimerComposant,ui);
    pageButton(ui.AllouerComposant,ui.PageAllouerComposant,ui);
    pageButton(ui.RetourComposant,ui.PageRetourComposant,ui);

    pageButton(ui.RechercheMembre,ui.PageRechercheMembre,ui);
    pageButton(ui.RechercheComposant,ui.PageRechercheComposant,ui);

    FonctionAjouterMembre(ui);
    FonctionModifierMembre(ui);
    FonctionSupprimerMembre(ui);

    FonctionAjouterComposant(ui);
    FonctionModifierComposant(ui);
    FonctionSupprimerComposant(ui);
    FonctionAllouerComposant(ui);
    FonctionRetournerComposant(ui);

    FonctionRechercheMembre(ui);
    FonctionRechercheComposant(ui);



    loadMembersFromFile("members.txt");
    loadComponentsFromFile("components.txt");
    loadAllocationsFromFile("allocations.txt");
    QObject::connect(&app, &QApplication::aboutToQuit, &closing);

    label.show();

    window.setWindowTitle("Gestion Des Materiels CPU");
    window.setWindowIcon(QIcon("C++.png"));
    label.setWindowIcon(QIcon("C++.png"));
    QTimer::singleShot(6100, [&]() {
        label.close();
        window.showMaximized();
    });
    return app.exec();
}