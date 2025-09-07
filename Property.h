#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
#include "Agent.h"

class Property {
private:
    float sellingPrice;
    int postalCode;
    float size;
    std::string type;
    int roomType;
    Agent agent;

public:
    // Constructor
    Property(float sPrice, int pCode, float size, const std::string& pType,
             const Agent& pAgent, int rType);

    // Getters and Setters
    void setSellingPrice(float price) { this->sellingPrice = price; }
    void setPostalCode(int code) { this->postalCode = code; }
    void setSize(float s) { this->size = s; }
    void setType(const std::string& t) { this->type = t; }
    void setRoomType(int r) { this->roomType = r; }
    void setAgent(const Agent& a) { this->agent = a; }

    float getSellingPrice() const { return sellingPrice; }
    int getPostalCode() const { return postalCode; }
    float getSize() const { return size; }
    std::string getType() const { return type; }
    int getRoomType() const { return roomType; }
    Agent getAgent() const { return agent; }
};

// Constructor implementation
Property::Property(float sPrice, int pCode, float size, const std::string& pType,
                   const Agent& pAgent, int rType)
    : sellingPrice(sPrice), postalCode(pCode), size(size), type(pType), agent(pAgent), roomType(rType) {}

#endif // PROPERTY_H