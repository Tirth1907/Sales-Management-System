#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>
#include <stdexcept>

using std::string;
class Data
{
	private :
		string AgentId,Contact,PropertySize,RoomType,Location,SellingPrice;
	public :
		Data():AgentId(),Contact(), PropertySize(),RoomType(),Location(),SellingPrice(){};
		Data(string AgentId, string Contact, string PropertySize, string RoomType, string Location, string SellingPrice);
		void setAgentId(string x){this->AgentId=x;}
		void setContact(string x){this->Contact=x;}
		void setPropertySize(string x){this->PropertySize=x;}
		void setRoomType(string x){this->RoomType=x;}
		void setLocation(string x){this->Location=x;}
		void setSellingPrice(string x){this->SellingPrice=x;}
		string getAgentId() const {return this->AgentId;}
		string getContact() const {return this->Contact;}
		string getPropertySize() const {return this->PropertySize;}
		string getRoomType() const {return this->RoomType;}
		string getLocation() const {return this->Location;}
		string getSellingPrice() const {return this->SellingPrice;}
		bool operator>(const Data& a) const;
		bool operator<(const Data& a) const;
};
Data::Data(string AgentId, string Contact, string PropertySize, string RoomType, string Location, string SellingPrice)
{
	this->AgentId=AgentId;
	this->Contact=Contact;
	this->PropertySize=PropertySize;
	this->RoomType=RoomType;
	this->Location=Location;
	this->SellingPrice=SellingPrice;
}
bool Data::operator>(const Data& a) const
{
	try {
        int thisPrice = std::stoi(this->SellingPrice);
        int otherPrice = std::stoi(a.getSellingPrice());
        return thisPrice > otherPrice;
    } catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid selling price format: " << ia.what() << std::endl;
        return false;
    }
}
bool Data::operator<(const Data& a) const
{
	try {
        int thisPrice = std::stoi(this->SellingPrice);
        int otherPrice = std::stoi(a.getSellingPrice());
        return thisPrice < otherPrice;
    } catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid selling price format: " << ia.what() << std::endl;
        return false;
    }
}
#endif