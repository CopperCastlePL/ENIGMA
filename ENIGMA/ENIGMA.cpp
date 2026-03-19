#include <iostream>
using namespace std;

void copy_array(int length, int* array1, int* array2)
{
    for (int i = 0; i < length; i++)
    {
        array2[i] = array1[i];
    }
    return;
}

void true_copy_array(int length, int ** the_array1, int* the_arrayofobj)
{
    int* new_array = new int[length];
    copy_array(length, the_arrayofobj, new_array);
    delete[] *the_array1;
    *the_array1 = new_array;
}

class rotor {
private:
public:

    int number_of_letters_of_this_rotor; //ilosc liter
    int number_of_notches_of_this_rotor; //ilosc notchy
    int* permutation;                    //tablica permutacji
    int* wires;                          //tabela kabli/sum
    int* b_wires;
    int* notches;                        //tablica notchy



    int position = 0;                    //pozycja
    bool test = false;

    rotor() {
        number_of_letters_of_this_rotor = NULL;
        permutation = new int[0];
        wires = new int[0];
        b_wires = new int[0];
        notches = new int[0];

        number_of_notches_of_this_rotor = NULL; //ilosc notchy
    }
    rotor(int number_of_letters, int number_of_notches) {
        permutation = new int[number_of_letters];
        notches = new int[number_of_notches];
        wires = new int[number_of_letters];
        b_wires = new int[number_of_letters];

        number_of_notches_of_this_rotor = number_of_notches;
        number_of_letters_of_this_rotor = number_of_letters;
        test = false;

    }
    void fill_wires() //przeniesc do prywatnych?
    {
        for (int i = 0; i < number_of_letters_of_this_rotor; i++)
        {
            // wires[i] = ((i + 1) - permutation[i])%number_of_letters_of_this_rotor;
            wires[i] = (permutation[i] - (i + 1)) % number_of_letters_of_this_rotor;
            b_wires[permutation[i] - 1] = ((i + 1) - permutation[i]) % number_of_letters_of_this_rotor;
            if (wires[i] < 0)
            {
                wires[i] += number_of_letters_of_this_rotor;
            }
            if (b_wires[i] < 0)
            {
                b_wires[i] += number_of_letters_of_this_rotor;
            }
            //cout << i+1 << "+" << wires[i] << " " << i+1<<endl;
        }
    }
    /*
    void display_wires(int pos) const
    {
        int a_pos = pos - 1;
        for (int i = 0; i < number_of_letters_of_this_rotor; i++)
        {
            cout << i + 1 << "+" << wires[(i + a_pos) % number_of_letters_of_this_rotor] << " " << i + 1 << endl; //TA DZIELENIE PRZEZ 4
        }
        cout << "-----" << endl;
    }
    void display_b_wires(int pos) const
    {
        int a_pos = pos - 1;
        for (int i = 0; i < number_of_letters_of_this_rotor; i++)
        {
            cout << i + 1 << "+" << b_wires[(i + a_pos) % number_of_letters_of_this_rotor] << " " << i + 1 << endl; //TA DZIELENIE PRZEZ 4
        }
        cout << "-----" << endl;
    }
    */
    void set_position(int number)
    {
        position = (number - 1) % number_of_letters_of_this_rotor; //0 1 2 3
    }
    void simple_rotation()
    {
        position++;
        position = position % number_of_letters_of_this_rotor;
    }
    int signal(int letter) const //wysyłanie sygnału BEZ OBROTU
    {
        int Al = letter - 1; //gupie amerykanskie numerowanie mozna zamiast tego dodac jeden do dzielenia
        //cout << "SYGNAL " << Al + wires[Al + position] << " % " << number_of_letters_of_this_rotor << " +1"<<endl;
        return ((Al + wires[(Al + position) % number_of_letters_of_this_rotor]) % number_of_letters_of_this_rotor) + 1; //cos zle

       // return ()
    }
    int back_signal(int letter) const
    {
        int Al = letter - 1;
        return ((Al + b_wires[(Al + position) % number_of_letters_of_this_rotor]) % number_of_letters_of_this_rotor) + 1; //byc moze -position
    }
    bool notch_lock() const
    {
        for (int i = 0; i < number_of_notches_of_this_rotor; i++)
        {
            if (position + 1 == notches[i])//jeden bo pozycje numeruje od 0
                return true;
        }
        return false;
    }
    bool notch_on_next() const
    {
        for (int i = 0; i < number_of_notches_of_this_rotor; i++)
        {
            if ((position + 1) % number_of_letters_of_this_rotor + 1 == notches[i])
                return true;
        }
        return false;
    }
    
   
   
   
   void copy(rotor &obj)
   {
       number_of_letters_of_this_rotor = obj.number_of_letters_of_this_rotor;
       number_of_notches_of_this_rotor = obj.number_of_notches_of_this_rotor;
       true_copy_array(number_of_letters_of_this_rotor, &permutation, obj.permutation);
       true_copy_array(number_of_letters_of_this_rotor, &wires, obj.wires);
       true_copy_array(number_of_letters_of_this_rotor, &b_wires, obj.b_wires);
       true_copy_array(number_of_notches_of_this_rotor, &notches, obj.notches);
   }

   //~rotor(){}

};

class reflector {
private:
public:
    int* permutation;
    int number_of_letters_of_reflector = 0;
    reflector() {
        permutation = new int[0]; //1
    }
    explicit reflector(int number_of_letters) { ///???????????????? explcit????????????????
        permutation = new int[number_of_letters];
        number_of_letters_of_reflector = number_of_letters;
    }
    int signal(int letter) const
    {
        int Al = letter - 1;
        return (permutation[Al]);
    }

    void copy(reflector &obj)
    {
        number_of_letters_of_reflector = obj.number_of_letters_of_reflector;
        int* new_permutation = new int[obj.number_of_letters_of_reflector];
        copy_array(obj.number_of_letters_of_reflector, obj.permutation, new_permutation);
        delete[] permutation;
        permutation = new_permutation;

    }
    
    ~reflector()
    {
       // delete[] permutation;
    }
    
};


int main()
{
    ////rotory
    int number_of_letters; //liczba liter w alfabecie
    int number_of_rottors; //liczba wirników w szafie
    //cout << "liczba liter"<<endl;//...
    cin >> number_of_letters;
    // cout << "Ile istnieje rotorow" << endl; //...
    cin >> number_of_rottors;
    rotor* rottors_array = new rotor[number_of_rottors]; //tablica wirników

    for (int i = 0; i < number_of_rottors; i++)
    {
        // cout << "PERMUTACJA" << endl;
        int* x = new int[number_of_letters];
        for (int j = 0; j < number_of_letters; j++)
        {
            cin >> x[j];
        }
        // cout << "NOTCHE" << endl;
        int number_of_notches;
        cin >> number_of_notches;
        int* y = new int[number_of_notches];
        for (int j = 0; j < number_of_notches; j++)
        {
            cin >> y[j];
        }

        rotor tmp(number_of_letters, number_of_notches);
        copy_array(number_of_letters, x, tmp.permutation);
        copy_array(number_of_notches, y, tmp.notches);
        tmp.fill_wires(); //przenieść to do prywatnych

        //rottors_array[i] = tmp;
        rottors_array[i].copy(tmp);

    }

    ///reflektory
    // cout << "ILE ISTNIEJE REFLEKTOROW" << endl;
    int number_of_reflectors; //liczba dostepnych do wyboru reflektorow
    cin >> number_of_reflectors;
    reflector* reflector_array = new reflector[number_of_reflectors]; //tablica reflektorów
    for (int i = 0; i < number_of_reflectors; i++)
    {
        //cout << "PERMUTACJA REFLEKTORA" << endl;
        int* z = new int[number_of_letters];
        for (int j = 0; j < number_of_letters; j++)
        {
            cin >> z[j];
        }
        //reflector *tmp= new reflector(number_of_letters);
        reflector tmp(number_of_letters);

        copy_array(number_of_letters, z, tmp.permutation);
        //reflector_array[i] = ///////////////////tmp;
        reflector_array[i].copy(tmp);

        delete[] z;
    }

    // cout << "ZADANIA" << endl;
    int p;
    cin >> p;

    for (int i = 0; i < p; i++)
    {
        //liczba rotorów w tym zadaniu
        //  cout << "liczba rotorow na osi" << endl;
        int n_rottors_in_task;
        cin >> n_rottors_in_task;
        rotor* axis = new rotor[n_rottors_in_task]; //oś rotorów


        for (int j = 0; j < n_rottors_in_task; j++)
        {
            //  cout << "wybierz index rotora na os" << endl;
            int tmp_index;
            cin >> tmp_index;
            axis[j] = rottors_array[tmp_index];
            //axis[j].copy(rottors_array[tmp_index]);

            // cout << "WYBIERZ POZYCJE ROTORA (w ktorej jest (nie na osi))"<<endl;
            int position;
            cin >> position;
            axis[j].set_position(position);

        }
        //cout << "WYBIERZ INDEX REFLECTORA" << endl;
        reflector TheReflector;
        int reflector_index;
        cin >> reflector_index;
        //TheReflector = reflector_array[reflector_index];
        TheReflector.copy(reflector_array[reflector_index]); ////TUUUUUUUUUU


        //koniec wprowadzania
        int x = -1000;


        for (int k = 0; x != 0; k++)
        {
            if (n_rottors_in_task > 2)
            {

                if (axis[1].notch_on_next() == true && axis[1].test == true && axis[0].test == true) //nocz nastepny 
                {
                    axis[2].simple_rotation();
                    //axis[2].test = true;
                    axis[1].simple_rotation();
                    //axis[1].test = true;

                }
                else if (axis[0].notch_on_next() == true && axis[0].test == true)
                {
                    axis[1].simple_rotation();
                    axis[1].test = true;
                }
            }
            else if (n_rottors_in_task > 1)
            {
                if (axis[0].notch_on_next() == true && axis[0].test == true) //zmienić na notch on current i dodac tu axis simple rotation
                {
                    axis[1].simple_rotation();
                    axis[1].test = true;
                }
            }

            axis[0].simple_rotation();
            axis[0].test = true;

            //przesył sygnału
            cin >> x;
            if (x != 0)
            {
                int signal = x;

                for (int j = 0; j < n_rottors_in_task; j++)
                {
                    signal = axis[j].signal(signal);
                }
                signal = TheReflector.signal(signal);
                for (int j = n_rottors_in_task - 1; j >= 0; j--)
                {
                    signal = axis[j].back_signal(signal);
                }

                cout << signal << " ";
            }

        }
        cout << endl;

        delete[] axis;
    }

    delete[] rottors_array;
    delete[] reflector_array;
}