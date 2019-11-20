#pragma once

#include <iostream>

class Chair {
public:
    Chair() {
        std::cout << "Create Chair" << std::endl;
    }
};

class WoodenChair: public Chair {
public:
    WoodenChair() {
        std::cout << "Create Wooden Chair" << std::endl;
    }
};

class MetalChair: public Chair {
public:
    MetalChair() {
        std::cout << "Create Metal Chair" << std::endl;
    }
};

class MetalRichChair: public MetalChair {
public:
    MetalRichChair() {
        std::cout << "Create Metal Rich Chair" << std::endl;
    }
};

class MetalPoorChair: public MetalChair {
public:
    MetalPoorChair() {
        std::cout << "Create Metal Poor Chair" << std::endl;
    }
};

class WoodenPoorChair: public WoodenChair {
public:
    WoodenPoorChair() {
        std::cout << "Create Wooden Poor Chair" << std::endl;
    }
};

class Table {
public:
    Table() {
        std::cout << "Create Table" << std::endl;
    }
};

class WoodenTable: public Table {
public:
    WoodenTable() {
        std::cout << "Create Wooden Table" << std::endl;
    }
};

class MetalTable: public Table {
public:
    MetalTable() {
        std::cout << "Create Metal Table" << std::endl;
    }
};

class MetalRichTable: public MetalTable {
public:
    MetalRichTable() {
        std::cout << "Create Metal Rich Table" << std::endl;
    }
};

class MetalPoorTable: public MetalTable {
public:
    MetalPoorTable() {
        std::cout << "Create Metal Poor Table" << std::endl;
    }
};

class Sofa {
public:
    Sofa() {
        std::cout << "Create Sofa" << std::endl;
    }
};

class WoodenSofa: public Sofa {
public:
    WoodenSofa() {
        std::cout << "Create Wooden Sofa" << std::endl;
    }
};

class MetalSofa: public Sofa {
public:
    MetalSofa() {
        std::cout << "Create Metal Sofa" << std::endl;
    }
};

class MetalRichSofa: public MetalSofa {
public:
    MetalRichSofa() {
        std::cout << "Create Metal Rich Sofa" << std::endl;
    }
};

class MetalPoorSofa: public MetalSofa {
public:
    MetalPoorSofa() {
        std::cout << "Create Metal Poor Sofa" << std::endl;
    }
};
