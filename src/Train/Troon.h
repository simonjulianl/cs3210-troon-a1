#ifndef CS3210_A1_A1_A0196678A_A0219768L_TROON_H
#define CS3210_A1_A1_A0196678A_A0219768L_TROON_H


class Troon {
public:
    int id;

    explicit Troon(int id) : id{id} {};

    bool operator<(Troon const &obj) const {
        return this->id < obj.id;
    };

    bool operator==(Troon const &obj) const {
        return this->id == obj.id;
    };

    bool operator!=(Troon const &obj) const {
        return this->id != obj.id;
    };
};


#endif //CS3210_A1_A1_A0196678A_A0219768L_TROON_H
