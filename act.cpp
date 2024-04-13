#include <iostream>

using namespace std;

template<class T>
class ColaDinamica;

template<class T>
class node
{
    private:
        T data;
        node<T>* sig;

    public:
        node() : sig(nullptr) {};
        node(T data) : data(data), sig(nullptr) {}

        friend class ColaDinamica<T>;
};

template<class T>
class ColaDinamica
{
    private:
        node<T>* frente;
        node<T>* fondo;

    public:
        ColaDinamica() : frente(nullptr), fondo(nullptr) {};

        void encolar(const T& dato);
        bool desencolar();
        bool vacia() const;

        friend ostream& operator << (ostream& os, const ColaDinamica<T>& cola)
        {
            node<T>* temp = cola.frente;

            while (temp != nullptr) {
                os << temp -> dato << " ";
                temp = temp -> sig;
            }

        return os;
    }
};

template<class T>
void ColaDinamica<T>::encolar(const T& dato)
{
    node<T>* nuevoNodo = new node<T>(dato);
    if (vacia())
    {
        frente = nuevoNodo;
    }
    else
    {
        fondo -> sig = nuevoNodo;
    }

    fondo = nuevoNodo;
}

template<class T>
bool ColaDinamica<T>::desencolar()
{
    if (vacia())
    {
        return false;
    }

    node<T>* temp = frente;
    frente = frente -> sig;
    delete temp;

    if (frente == nullptr)
    {
        fondo = nullptr;
    }

    return true;
}

template<class T>
bool ColaDinamica<T>::vacia() const
{
    return frente == nullptr;
}

class SolicitudConstancia
{
    private:
    string nombreAlumno;
    string carrera;
    int materiasAprobadas;
    float promedioGeneral;

    public:
        SolicitudConstancia() : nombreAlumno(""), carrera(""), materiasAprobadas(0), promedioGeneral(0.0f) {}
        SolicitudConstancia(const string& nombre, const string& carrera, int materiasAprobadas, float promedioGeneral) : nombreAlumno(nombre), carrera(carrera), materiasAprobadas(materiasAprobadas), promedioGeneral(promedioGeneral) {}

        bool operator == (const SolicitudConstancia& otro) const
        {
            return nombreAlumno == otro.nombreAlumno;
        }

        friend class ColaDinamica<SolicitudConstancia>;

        friend ostream& operator<<(ostream& os, const SolicitudConstancia& solicitud) {
            os << "Nombre del alumno: " << solicitud.nombreAlumno << endl;
            os << "Carrera: " << solicitud.carrera << endl;
            os << "Materias aprobadas: " << solicitud.materiasAprobadas << endl;
            os << "Promedio general: " << solicitud.promedioGeneral << endl;
            return os;
        }
};

int main()
{
    ColaDinamica<SolicitudConstancia> ColaSolicitudes;

    int opcion;
    do
    {
        cout << "\nMenú:\n"
        << "1. Dar de alta solicitud de un Alumno\n"
        << "2. Elaborar Constancia\n"
        << "3. Salir\n" << endl
        << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1:
            {
                string nombre;
                string carrera;
                int materiasAprobadas;
                float promedioGeneral;

                cout << "Ingrese el nombre del alumno: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese la carrera del alumno: ";
                getline(cin, carrera);
                cout << "Ingrese el total de materias aprobadas: ";
                cin >> materiasAprobadas;
                cout << "Ingrese el promedio general del alumno: ";
                cin >> promedioGeneral;

                SolicitudConstancia solicitud(nombre, carrera, materiasAprobadas, promedioGeneral);
                ColaSolicitudes.encolar(solicitud);

                cout << endl << "Solicitud de constancia de " << nombre << " encolada correctamente." << endl;
                break;
            }

            case 2:
            {
                if (!ColaSolicitudes.vacia())
                {
                    SolicitudConstancia solicitud;
                    
                    if (ColaSolicitudes.desencolar())
                    {
                        cout << endl << "Constancia elaborada para: " << solicitud << endl;
                    }
                    else
                    {
                        cout << endl << "No hay solicitudes en espera." << endl;
                    }
                }
                else
                {
                    cout << endl << "No hay solicitudes en espera." << endl;
                }

                break;
            }

            case 3:
            {
                cout << endl << "Saliendo del programa." << endl;
                return 0;
                break;
            }

            default:
            {
                cout << endl << "Opción inválida, por favor seleccione nuevamente." << endl;
                break;
            }
        }
    } while (opcion != 6);

    return 0;
}
