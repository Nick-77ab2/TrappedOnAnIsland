#ifndef _HUMAN_H_
#define _HUMAN_H_
#include <string>

class Human{
    private:
        std::string type;
        std::string name;
        int rows;
        bool onMainland;
        bool onIsland;
    
    public:
        Human(std::string t, std::string n, int r, bool m, bool i);
        std::string getType();
        std::string getName();
        void addRows(int r);
        void resetRows();
        int getRows();
        void setMainland(bool m);
        bool getMainland();
        void setIsland(bool i);
        bool getIsland();
};

#endif