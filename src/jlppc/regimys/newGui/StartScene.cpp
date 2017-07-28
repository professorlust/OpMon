#include "StartScene.hpp"
#include "../start/main.hpp"
#include "Animations.hpp"
#include "MainFrame.hpp"

UNS

namespace MainFrame {
    sf::Sprite arrDial;
    namespace StartScene {
//Déclaration des SDL_Rect et des SDL_Texture secondaires, necessaires a cette scene (a détruire)
        sf::Sprite fondT;
        sf::Sprite profT;

        sf::Sprite textUre;
        sf::Music fondMus;
//Déclaration des variables utilitaires (sera supprimé en cours de travail)
//Part 0
        bool continuer = true;
        long ancientTick = 0;
        sf::String txtP0[18];//Deux cases == Deux lignes. 3 cases == Deux lignes + un nouveau dialogue
        int sizeOfTxt = 18;
        sf::String txtEnCours[] = {sf::String(" "), sf::String(" "), sf::String(" ")};
//SDL_Surface *sfce = NULL;
        int line = 0, i = 0, dialog = 0;
        bool changeDialog = false;
        int phase = 0;
        bool joypressed = false;
//Part 1
        char pName[16] = "               ";
        int k = 0;
        sf::Sprite fondNE;
        sf::Text texteDescs[4];//To destroy in part 1
        sf::Text nameT;//To destroy in part 1
        bool shift = false;
        bool caps = false;
//Part 2
        sf::String txtP1[15];

        sf::Texture textures[5];

        void initStrings() {
            unsigned int it = 0;
            for(it = 0; it < 18; it++) {
                    ostringstream oss;
                    oss << "prof.dialog.start." << it + 1;
                    txtP0[it] = kget(oss.str());
                }
            int ite = 1;
            it++;
            txtP1[0] = kget("prof.dialog.start.19");
            for(it = it; it < 27; it++) {
                    ostringstream oss;
                    oss << "prof.dialog.start." << it + 1;
                    txtP1[ite] = kget(oss.str());
                    ite++;
                }
            texteDescs[0].setString(kget("nameEntry.med"));

            texteDescs[1].setString(kget("nameEntry.top"));

            texteDescs[2].setString(kget("nameEntry.indic.1"));

            texteDescs[3].setString(kget("nameEntry.indic.2"));
        }

        void destroyVars() {

        }

        /**Initialise les variables*/
        void initVars() {
            initStrings();
            rlog << PRINT_TICKS << "Initialisation des variables de la scene d'intro" << endl;
            MainFrame::dialog.setPosition(0, 362);
            profT.setPosition((fondT.getGlobalBounds().height / 2) - (profT.getGlobalBounds().width / 2) + 10, ((fondT.getGlobalBounds().height - MainFrame::dialog.getGlobalBounds().height / 2) - (profT.getGlobalBounds().height / 2) + 50));
            texteDescs[1].setPosition(85, 25);
            texteDescs[0].setPosition(155, 200);
            texteDescs[2].setPosition(95, 375);
            texteDescs[3].setPosition(95, 405);


            txtEnCours[0] = sf::String(" ");
            txtEnCours[1] = sf::String(" ");
            txtEnCours[2] = sf::String(" ");
            sizeOfTxt = 18;
            changeDialog = false;
            phase = 0;
            joypressed = false;
            line = 0;
            i = 0;
            dialog = 0;
            //Initialisation des images
            rlog << PRINT_TICKS << "Initialisation des sprites..." << endl;
#ifdef _WIN32
            textures[0].loadFromFile("ressources\\backgrounds\\start\\startscene.png");
            textures[1].loadFromFile("ressources\\sprites\\chara\\jlppc\\profkiwai.png");
            textures[2].loadFromFile("ressources\\backgrounds\\dialog\\dialog.png");
            textures[3].loadFromFile("ressources\\sprites\\misc\\arrDial.png");
            textures[4].loadFromFile("ressources\\backgrounds\\start\\nameEntry.png");
#else
            textures[0].loadFromFile(RESSOURCES_PATH + "backgrounds/start/startscene.png");
            textures[1].loadFromFile(RESSOURCES_PATH + "sprites/chara/jlppc/profkiwai.png");
            textures[2].loadFromFile(RESSOURCES_PATH + "backgrounds/dialog/dialog.png");
            textures[3].loadFromFile(RESSOURCES_PATH + "sprites/misc/arrDial.png");
            textures[4].loadFromFile(RESSOURCES_PATH + "backgrounds/start/nameEntry.png");
#endif

            fondT.setTexture(textures[0]);
            profT.setTexture(textures[1]);
            MainFrame::dialog.setTexture(textures[2]);
            arrDial.setTexture(textures[3]);
            fondNE.setTexture(textures[4]);
            fondNE.setPosition(0, 0);
            fondMus.setLoop(true);

            profT.setPosition(205, 120);
            profT.setScale(1.5, 1.5);


            rlog << PRINT_TICKS << "Fin des initialisations" << endl;
            for(unsigned int iterator = 0; iterator < 4; iterator++) {
                    texteDescs[iterator].setCharacterSize(FONT_SIZE_DEFAULT);
                    texteDescs[iterator].setColor(sf::Color::Black);
                    texteDescs[iterator].setFont(font);
                }

            nameT.setFont(font);
            nameT.setPosition(120, 300);

#ifdef _WIN32
            fondMus.openFromFile("ressources\\audio\\music\\intro.ogg");
#else
            fondMus.openFromFile(RESSOURCES_PATH + "audio/music/intro.ogg");
#endif
            arrDial.setPosition(512-75, 512-30);
        }

        /**Verifie les erreurs de variables*/
        int verifVars() {
        }

        int boucle0() {
            rlog << PRINT_TICKS << "Début de la boucle n°0" << endl;
            //Boucle n°1
            while (continuer) {
                    if ((ticks.getElapsedTime().asMilliseconds() - ancientTick) >= FPS_TICKS) {

                            ancientTick = ticks.getElapsedTime().asMilliseconds();

                            window.pollEvent(events);

                            switch (events.type) {

                                        QUIT

                                    case sf::Event::KeyPressed:
                                        if(events.key.code == sf::Keyboard::Space) {
                                                DIALOG_PASS(txtP0)
                                            }
                                        break;

                                }

                            ECHAP
                            else if(isKeyPressed(sf::Keyboard::P)) {
                                    return 2;
                                }
                            if (phase == 0) {
                                    frame.clear(sf::Color::White);
                                    frame.draw(fondT);
                                    frame.draw(profT);
                                    frame.draw(MainFrame::dialog);
                                    if (!changeDialog) {
                                            //Affichage caractère par caractère
                                            if (!(i >= txtP0[line + dialog].toUtf32().size())) {

                                                    if (txtEnCours[line] == sf::String(" ")) {
                                                            txtEnCours[line] = txtP0[line + dialog].toUtf32()[i];
                                                        }
                                                    else {
                                                            txtEnCours[line] += txtP0[line + dialog].toUtf32()[i];

                                                        }

                                                    i++;
                                                }
                                            else {
                                                    if (line == 2) {
                                                            changeDialog = true;
                                                        }
                                                    else {
                                                            line++;
                                                            i = 0;
                                                        }
                                                }





                                        }
                                    sf::String tab[3] = {txtEnCours[0], txtEnCours[1], txtEnCours[2]};
                                    printText(frame, tab);
                                    ANIM_ARROW
                                    frame.display();
                                    winRefresh();
                                }
                            else {
                                    break;
                                }


                        }
                    else {
                            Utils::wait(FPS_TICKS - (GET_TICKS - ancientTick));
                        }

                }
            return 0;
        }

        int boucle1() {
            window.setKeyRepeatEnabled(true);
            frame.clear(sf::Color::White);
            frame.draw(fondNE);
            FOR_EACH(sf::Text, texteDescs, 4, {)
                     objActuel->setColor(sf::Color::White);
                     frame.draw(*objActuel);
                    }
            frame.display();
            winRefresh();
            while (continuer) {
                    window.waitEvent(events);
                    switch (events.type) {
                                QUIT

                            case sf::Event::TextEntered:
                                if(events.text.unicode == 8) { //Backspace
                                        pName[k] = ' ';
                                        if (k != 0) {
                                                k--;
                                            }
                                    }
                                else if(events.text.unicode == '\n' || events.text.unicode < 32) {
                                    }
                                else {
                                        if (k != 14) {
                                                k++;
                                            }
                                        pName[k] = events.text.unicode;
                                    }
                                break;

                            case sf::Event::KeyPressed:
                                if(events.key.code == sf::Keyboard::Return) {
                                        bool voided = true;
                                        int voidNumber = 0;
                                        int indexEnd = 0;
                                        for (unsigned int l = 0; l < 15; l++) {
                                                if (pName[l] != ' ') {
                                                        voided = false;
                                                        voidNumber = 0;
                                                    }
                                                else {
                                                        voidNumber++;
                                                    }
                                                if (voidNumber >= 2) {
                                                        indexEnd = l - 1;
                                                        break;
                                                    }
                                            }
                                        if (voided) {
                                                pName[0] = ' ';
                                                pName[0 + 1] = 'P';
                                                pName[1 + 1] = 'i';
                                                pName[2 + 1] = 'e';
                                                pName[3 + 1] = 'r';
                                                pName[4 + 1] = 'r';
                                                pName[5 + 1] = 'e';
                                                pName[6 + 1] = '\0';
                                            }
                                        else {
                                                if(indexEnd != 0) {
                                                        pName[indexEnd] = '\0';
                                                    }
                                            }
                                        continuer = false;
                                    }

                        }

                    ECHAP

                    frame.clear(sf::Color::White);
                    frame.draw(fondNE);
                    FOR_EACH(sf::Text, texteDescs, 4, {)
                             objActuel->setColor(sf::Color::White);
                             frame.draw(*objActuel);
                    }
		    nameT.setString(string(pName));
		    Main::player.setName(string(pName));
                    frame.draw(nameT);
                    frame.display();
                    winRefresh();


                }
            window.setKeyRepeatEnabled(false);
            return 0;
        }

        int boucle2() {

            while (continuer) {
                    if ((GET_TICKS - ancientTick) >= FPS_TICKS) {

                            ancientTick = GET_TICKS;

                            window.pollEvent(events);

                            switch (events.type) {

                                        QUIT

                                    case sf::Event::KeyPressed:
                                        if(events.key.code == sf::Keyboard::Space) {
                                                DIALOG_PASS(txtP1);
                                            }
                                }
                            ECHAP
                            if (phase == 2) {
                                    frame.clear(sf::Color::White);
                                    frame.draw(fondT);
                                    frame.draw(profT);
                                    frame.draw(MainFrame::dialog);
                                    if (!changeDialog) {

                                            if (!(i >= txtP1[line + dialog].toUtf32().size())) {

                                                    if (txtEnCours[line] == " ") {
                                                            txtEnCours[line] = txtP1[line + dialog].toUtf32()[i];
                                                        }
                                                    else {
                                                            txtEnCours[line] += txtP1[line + dialog].toUtf32()[i];
                                                        }

                                                    i++;
                                                }
                                            else {
                                                    if (line == 2) {
                                                            changeDialog = true;
                                                        }
                                                    else {
                                                            line++;
                                                            i = 0;
                                                        }
                                                }





                                        }
                                    sf::String tab[3] = {txtEnCours[0], txtEnCours[1], txtEnCours[2]};
                                    printText(frame, tab);
                                    ANIM_ARROW
                                    frame.display();
                                    winRefresh();
                                }
                            else {
                                    return 0;
                                }


                        }
                    else {
                            Utils::wait(FPS_TICKS - (GET_TICKS - ancientTick));
                        }
                }
            return 0;
        }

        int startScene() {
            verifVars();
            //Départ de la musique
            fondMus.play();

            //Initialisation des tailles

            //Vesrification des problèmes possibles

            //Initialisation des variables utiles pour la boucle
            frame.display();
            winRefresh();
            int result = boucle0();
            if(result == -1) {
                    return -1;
                }
            else if(result == 2) {
                    ;
                    return 2;
                }

            continuer = true;



            phase = 1;
            rlog << PRINT_TICKS << "Chargement de la boucle n°1" << endl;

            //Animation 1
            Animations::animFenOpen(frame, fondT);

            rlog << PRINT_TICKS << "Début de la boucle n°1" << endl;

            if(boucle1() == -1) {

                    return -1;
                }

            continuer = true;
            //Animation 2
            Animations::animFenClose(frame, fondT);

            txtP1[0]+=(string(pName) + kget("prof.dialog.start.19.5"));

            phase = 2;

            sizeOfTxt = 27 - 18;
            i = 0;
            line = 0;
            dialog = 0;
            txtEnCours[0] = sf::String(" ");
            txtEnCours[1] = sf::String(" ");
            txtEnCours[2] = sf::String(" ");
            changeDialog = false;
            rlog << PRINT_TICKS << "Début de la boucle n°2" << endl;
            if(boucle2() == -1) {
                    return -1;
                }
            fondMus.stop();
            phase++;
            return 0;


        }
    }
}

