#ifndef ALIMENTATION_H
#define ALIMENTATION_H


class Alimentation
{
public:
    Alimentation();
    ~Alimentation();

    void setEnergie(double energie);
    double getEnergie();

    void setCourantEmission(double courant);
    double getCourantEmission();

    void setMode(bool mode);
    bool getMode();

    void setFocus(double focus);
    double getFocus();

    void setWehnelt(double wehnelt);
    double getWehnelt();

    void setPositionX(double posX);
    double getPositionX();

    void setPositionY(double posX);
    double getPositionY();

    void setBalayageX(double balayage);
    double getBalayageX();

    void setBalayageY(double balayage);
    double getBalayageY();

private:
    double m_energie;
    double m_courantEmission;
    bool m_mode;
    double m_focus;
    double m_wehnelt;
    double m_positionX;
    double m_positionY;
    double m_balayageX;
    double m_balayageY;

};




#endif // ALIMENTATION_H
