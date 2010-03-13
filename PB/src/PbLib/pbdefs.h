#pragma once

/*
#define IMPL_GET_SET(type, name) private:type _##name;public:type get##name(){return _##name;} void set##name(type _arg){_##name = _arg;}

#define IMPL_GET_SET_3(tfield, tget, tset,n) private:tfield _##n;public:tget get##n(){return _##n;} void set##n(tset __arg){_##n=static_cast<tfield>(__arg);}

template<class T, T def> struct Initialized
{
	Initialized() : _value(def){}
	operator T&(){ return _value; }
	T _value;
};

*/


typedef QString PBPlayerId;
typedef QString PBHandId;
typedef QString PBCards;

class PBSeatedPlayer;
class PBGame;
class PBTable;
class PBSeats;