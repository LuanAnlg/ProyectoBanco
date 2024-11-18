#include "Fecha.h"
#include "Monto.h"
#include "Identidad.h"
#include "Contacto.h"
#include "Usuario.h"
#include "Tarjeta.h"
#include "Transaccion.h"
#include "Cuenta.h"
#include "Queja.h"
#include "MQuejas.h"
#include "Cliente.h"
#include "UCliente.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
int main()
{
	srand(time(NULL));
	Fecha f;
	f.generateRandom();
	cout << f.toDebug() << endl;
	Monto m;
	m.generateRandom();
	cout << m.toDebug() << endl << endl;
	Identidad i;
	i.generateRandom();
	cout << i.toDebug() << endl << endl;
	Contacto c;
	c.generateRandom();
	cout << c.toDebug() << endl << endl;
	Usuario u;
	cout << u.toDebug() << endl << endl;
	Tarjeta t;
	t.generateRandom();
	cout << t.toDebug() << endl << endl;
	Transaccion tr;
	tr.generateRandom();
	cout << tr.toDebug() << endl << endl;
	/*Cuenta cu;
	cu.generateRandom();
	cout << cu.toDebug() << endl << endl;*/
	Queja q;
	q.generateRandom();
	cout << q.toDebug() << endl << endl;
	MQuejas mq(Fecha(), TipoUsuario::Cliente);
	mq.generateRandom();
	cout << mq.toDebug() << endl << endl;
	/*Cliente cl;
	cl.generateRandom();
	cout << cl.toDebug() << endl << endl;*/
	UCliente uc;
	uc.generateRandom();
	uc.interact();
}