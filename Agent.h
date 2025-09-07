#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <string>

class Agent {
private:
    std::string id;
    int contact;

public:
    // Constructor
    Agent(const std::string& agentId = "", int agentContact = 0);

    // Getters and Setters with correct names
    void setId(const std::string& agentId) { this->id = agentId; }
    void setContact(int agentContact) { this->contact = agentContact; }
    std::string getId() const { return id; }
    int getContact() const { return contact; }

    // Correctly overloaded assignment operator as a member function
    Agent& operator=(const Agent& a);
};

// Constructor implementation
Agent::Agent(const std::string& agentId, int agentContact) : id(agentId), contact(agentContact) {}

// Overloaded assignment operator implementation
Agent& Agent::operator=(const Agent& a) {
    if (this != &a) {
        // Corrected typos from getid and setid to getId and setId
        setId(a.getId());
        setContact(a.getContact());
    }
    return *this;
}

#endif // AGENT_H