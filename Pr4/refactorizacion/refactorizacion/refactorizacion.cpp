#include <iostream>

using namespace std;

//Atributos del enemigo
int enemy1HP = 100;
string enemy1Name = "Zombie";
bool enemy1Alive = true;

//Atributos del enemigo 2
int enemy2HP = 150;
string enemy2Name = "Creeper";
bool enemy2Alive = true;

//Atributos del personaje
int heroHP = 300;
int heroDamage;
string heroName;
bool heroAlive = true;

//Atributos del juego
int enemyChoosed = 0;
int magicPoints = 2;
int tortazo = 15;
int espadazo = 30;
int magic = 50;

void gameStart() {
    cout << "El enemigo " << enemy1Name << " ha aparecido\n";
    cout << "Introduce el nombre del heroe: \n";
    cin >> heroName;
    cout << "El nombre del heroe es " << heroName << "\n";
}


void checkEnemyStatus(string enemyName, int& enemyHP, bool& enemyAlive) {
    if (enemyHP <= 0) {
        cout << "Has matado al enemigo " << enemyName << " \n";
        enemyHP = 0;
        enemyAlive = false;
    }
    else {
        cout << "El enemigo " << enemyName << " tiene " << enemyHP << " puntos de vida\n";
        enemyAlive = true;
    }
}

void chooseEnemy(int& ChooseEnemy) {
    ChooseEnemy = 0;
    while (ChooseEnemy != 1 && ChooseEnemy != 2) {
        cout << "A que enemigo quieres atacar? \n";
        if (enemy1Alive) {
            cout << "1. " << enemy1Name << "\n";
        }
        if (enemy2Alive) {
            cout << "2. " << enemy2Name << "\n";
        }
        cin >> ChooseEnemy;
        if (ChooseEnemy <= 0 || ChooseEnemy > 2) {
            cout << "La opcion elegida no es correcta. Por favor, elige una opcion valida. \n";
        }
        if (!enemy1Alive && ChooseEnemy == 1) {
            cout << "El enemigo " << enemy1Name << " ya esta muerto. Por favor, elige un enemigo que todavia este vivo." " \n";
            ChooseEnemy = 0;
        }
        if (!enemy2Alive && ChooseEnemy == 2) {
            cout << "El enemigo " << enemy2Name << " ya esta muerto. Por favor, elige un enemigo que todavia este vivo." " \n";
            ChooseEnemy = 0;
        }
    }

}


void chooseAttack(int& ChooseAttack) {
    ChooseAttack = 0;
    while (ChooseAttack != 1 && ChooseAttack != 2 && ChooseAttack != 3) {
        cout << "Que ataque quieres usar? \n";
        cout << "1.- Espadazo \n";
        cout << "2.- Puñetazo \n";
        if (magicPoints > 0) {
            cout << "3.- Magia\n";
        }
        cin >> ChooseAttack;
        if (ChooseAttack <= 0 || ChooseAttack > 3) {
            cout << "El ataque seleccionado no es correcto. Por favor, elige una opcion valida. \n";
        }
        if (ChooseAttack == 3) {
            if (magicPoints > 0) {
                magicPoints--;
            }
            else {
                ChooseAttack = 0;
                cout << "No te queda magia. Por favor selecciona un ataque que puedas usar. \n";
            }
        }
    }
    if (ChooseAttack == 1) {
        ChooseAttack = espadazo;
    }
    else if (ChooseAttack == 2) {
        ChooseAttack = tortazo;
    }
    else {
        ChooseAttack = magic;
    }
}


void heroAttackEnemy(int damage, string enemyName, int& enemyHP) {
    cout << "Atacas al enemigo " << enemyName << " y le haces " << damage << " de daño" << "\n";
    enemyHP = enemyHP - damage;
}

void enemyAttack(int enemydamage, int& heroHP, string enemyName, bool& heroAlive) {
    heroHP = heroHP - enemydamage;
    if (heroHP > 0) {
        cout << "El enemigo " << enemyName << " te ha atacado y te quedan " << heroHP << " de vida\n";
    }
    else {
        cout << "El enemigo " << enemyName << " te ha atacado y te ha matado. GAME OVER \n";
        heroAlive = false;
    }
}

int main()
{
    gameStart();
    while (heroAlive && (enemy1Alive || enemy2Alive)) {
        //ELEGIMOS ENEMIGO AL QUE ATACAR
        chooseEnemy(enemyChoosed);
        //ELEGIMOS ATAQUE Y CAPTURAMOS EL VALOR DEL DANYO QUE HAREMOS
        chooseAttack(heroDamage);

        if (enemyChoosed == 1) {
            //ATACAMOS AL ENEMIGO 1
            heroAttackEnemy(heroDamage, enemy1Name, enemy1HP);
            checkEnemyStatus(enemy1Name, enemy1HP, enemy1Alive);
        }
        else {
            //ATACAMOS AL ENEMIGO 2
            heroAttackEnemy(heroDamage, enemy2Name, enemy2HP);
            checkEnemyStatus(enemy2Name, enemy2HP, enemy2Alive);

        }
        //ATACA EL ENEMIGO 1 SI ESTÁ VIVO Y EL HÉROE TAMBIÉN
        if (enemy1Alive && heroAlive) {
            enemyAttack(50 + rand() % 20, heroHP, enemy1Name, heroAlive);
        }
        //ATACA EL ENEMIGO 2 SI ESTÁ VIVO Y EL HÉROE TAMBIÉN
        if (enemy2Alive && heroAlive) {
            enemyAttack(50 + rand() % 20, heroHP, enemy2Name, heroAlive);
        }
    }
}