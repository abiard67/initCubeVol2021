/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TypeAck.h
 * Author: snir2g2
 *
 * Created on 19 mars 2019, 16:30
 */

#ifndef TYPEACK_H
#define TYPEACK_H
#include <string>
using namespace std;

class TypeAck {
	public:
		TypeAck();
		TypeAck(const TypeAck& orig);
		virtual ~TypeAck();
	public: static string OK;
	public: static string FAIL;
	public: static string BUSY;
	public: static string ERROR;
};

#endif /* TYPEACK_H */

