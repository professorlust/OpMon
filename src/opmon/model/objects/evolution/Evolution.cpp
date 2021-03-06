/*
Evolution.cpp
Author : Cyrion
File under GNU GPL v3.0 license
*/
#include "Evolution.hpp"

namespace OpMon {
    namespace Model {

        Evolution::Evolution(int evo)
          : evo(evo) {
        }

        void Evolution::checkEvo() {
            //toEvolve = Data::OpMons::listOp[evo];
        }

        Species *Evolution::getEvolution() const {
            return toEvolve;
        }

    } // namespace Model
} // namespace OpMon
