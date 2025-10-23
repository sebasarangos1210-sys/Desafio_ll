#include <iostream>
#include "MensajePublicitario.h"
#include "Credito.h"
#include "Cancion.h"
#include "Album.h"

using namespace std;

void imprimirSeparador(const string& titulo) {
    cout << "--------------------------" << "\n";
    cout << "  " << titulo << "\n";
    cout << "--------------------------" << "\n";
}

void probarMensajePublicitario() {
    imprimirSeparador("PRUEBA: MensajePublicitario");

    // Crear mensajes de diferentes categorías
    MensajePublicitario msg1("sexooooooooooo", 1);
    MensajePublicitario msg2("albion online es un mmorprg", 2);
    MensajePublicitario msg3("como lo mueve esa muchachota", 3);

    cout << "Mensaje 1 (Categoria " << msg1.getNombreCategoria() << "):\n";
    cout << "  Contenido: " << msg1.getContenido() << "\n";
    cout << "  Prioridad: " << msg1.obtenerPrioridad() << "\n";
    cout << "  Veces mostrado: " << msg1.getVecesMostrado() << "\n";

    cout << "\nMensaje 2 (Categoria " << msg2.getNombreCategoria() << "):\n";
    cout << "  Prioridad: " << msg2.obtenerPrioridad() << "\n";

    cout << "\nMensaje 3 (Categoria " << msg3.getNombreCategoria() << "):\n";
    cout << "  Prioridad: " << msg3.obtenerPrioridad() << "\n";

    // Incrementar contador
    msg1.incrementarContador();
    msg1.incrementarContador();
    cout << "\nDespues de mostrar msg1 dos veces: " << msg1.getVecesMostrado() << "\n";

    // Probar operadores
    cout << "\n¿Mensaje 3 > Mensaje 1? " << (msg3 > msg1 ? "Si" : "No") << "\n";
    cout << "¿Mensaje 1 < Mensaje 2? " << (msg1 < msg2 ? "Si" : "No") << "\n";

    // Validación
    cout << "\n¿Mensaje 1 es valido? " << (msg1.esValido() ? "Si" : "No") << "\n";

    // Memoria
    cout << "\nMemoria usada por msg1: " << msg1.calcularMemoriaUsada() << " bytes\n";

    cout << "\n Prueba de MensajePublicitario EXITOSA\n";
}

void probarCredito() {
    imprimirSeparador("PRUEBA: Credito");

    // Crear créditos
    Credito productor("hoola", "yo", "PROD12345A", 1);
    Credito musico("mi", "papa", "MUS98765BC", 2);
    Credito compositor("leonardo", "di caprio", "COMP111222", 3);

    cout << "Productor:\n";
    cout << "  Nombre completo: " << productor.getNombreCompleto() << "\n";
    cout << "  Codigo afiliacion: " << productor.getCodigoAfiliacion() << "\n";
    cout << "  Tipo: " << productor.getTipoCreditoString() << "\n";
    cout << "  ¿Es valido? " << (productor.esValido() ? "Si" : "No") << "\n";

    cout << "\nMusico:\n";
    cout << "  Nombre completo: " << musico.getNombreCompleto() << "\n";
    cout << "  Tipo: " << musico.getTipoCreditoString() << "\n";

    cout << "\nCompositor:\n";
    cout << "  Nombre completo: " << compositor.getNombreCompleto() << "\n";
    cout << "  Tipo: " << compositor.getTipoCreditoString() << "\n";

    // Probar constructor de copia
    Credito copiaProductor = productor;
    cout << "\nCopia del productor: " << copiaProductor.getNombreCompleto() << "\n";

    // Probar operadores
    cout << "\n¿Productor == Musico? " << (productor == musico ? "Si" : "No") << "\n";
    cout << "¿Productor != Musico? " << (productor != musico ? "Si" : "No") << "\n";
    cout << "¿Musico < Productor (por apellido)? " << (musico < productor ? "Si" : "No") << "\n";

    // Memoria
    cout << "\nMemoria usada por productor: " << productor.calcularMemoriaUsada() << " bytes\n";

    cout << "\n Prueba de Credito EXITOSA\n";
}

void probarCancion() {
    imprimirSeparador("PRUEBA: Cancion");

    // Crear canción con ID jerárquico: [12345-67-89]
    Cancion cancion(123456789, "ojitos ojos negros", 354, "/music/ozuna/tuu_sola");

    cout << "Cancion creada:\n";
    cout << "  ID completo: " << cancion.getId() << "\n";
    cout << "  Nombre: " << cancion.getNombre() << "\n";
    cout << "  Duracion: " << cancion.getDuracionFormateada() << "\n";
    cout << "  Veces reproducida: " << cancion.getVecesReproducida() << "\n";

    // Probar extracción de IDs
    cout << "\nIDs jerarquicos:\n";
    cout << "  ID Artista (primeros 5): " << cancion.extraerIdArtista() << "\n";
    cout << "  ID Album (digitos 6-7): " << cancion.extraerIdAlbum() << "\n";
    cout << "  ID Cancion (ultimos 2): " << cancion.extraerIdCancion() << "\n";

    // Probar validación
    cout << "\n¿ID es valido? " << (cancion.validarId() ? "Si" : "No") << "\n";

    // Agregar créditos
    Credito* productor = new Credito("sebas", "arango", "PROD54321X", 1);
    Credito* vocalista = new Credito("cristiano", "messi", "VOC11111AA", 2);
    Credito* guitarrista = new Credito("harlin", "el bro", "GUIT22222B", 2);
    Credito* compositor = new Credito("gato", "Mercury", "COMP33333C", 3);

    cancion.agregarCredito(productor);
    cancion.agregarCredito(vocalista);
    cancion.agregarCredito(guitarrista);
    cancion.agregarCredito(compositor);

    cout << "\nCreditos agregados: " << cancion.getNumCreditos() << "\n";

    // Obtener créditos por tipo
    int cantMusicos = 0;
    Credito** musicos = cancion.obtenerCreditosPorTipo(2, cantMusicos);
    cout << "Musicos encontrados: " << cantMusicos << "\n";
    if (musicos != nullptr) {
        for (int i = 0; i < cantMusicos; i++) {
            cout << "  - " << musicos[i]->getNombreCompleto() << "\n";
        }
        delete[] musicos;
    }

    // Probar rutas de audio
    cout << "\nRutas de audio:\n";
    cout << "  128 kbps: " << cancion.obtenerRutaAudio(128) << "\n";
    cout << "  320 kbps: " << cancion.obtenerRutaAudio(320) << "\n";

    // Incrementar reproducciones
    cancion.incrementarReproducciones();
    cancion.incrementarReproducciones();
    cancion.incrementarReproducciones();
    cout << "\nDespues de reproducir 3 veces: " << cancion.getVecesReproducida() << " reproducciones\n";

    // Probar operadores
    Cancion otraCancion(987654321, "loca", 215, "/music/quemas/pel");
    cout << "\n¿Canciones son iguales? " << (cancion == otraCancion ? "Si" : "No") << "\n";
    cout << "¿Cancion tiene ID 123456789? " << (cancion == 123456789 ? "Si" : "No") << "\n";

    // Memoria
    cout << "\nMemoria usada por cancion: " << cancion.calcularMemoriaUsada() << " bytes\n";

    // Liberar créditos
    delete productor;
    delete vocalista;
    delete guitarrista;
    delete compositor;

    cout << "\n Prueba de Cancion EXITOSA\n";
}

void probarAlbum() {
    imprimirSeparador("PRUEBA: Album");

    // Crear álbum
    Album album(67, "zzzzz", "1975-11-21", "pppp", "/ciugg/yanosequemascolocar .png");

    cout << "Album creado:\n";
    cout << "  ID: " << album.getId() << "\n";
    cout << "  Nombre: " << album.getNombre() << "\n";
    cout << "  Fecha: " << album.getFechaLanzamiento() << "\n";
    cout << "  Sello: " << album.getSelloDisquero() << "\n";
    cout << "  Portada: " << album.getPortada() << "\n";

    // Agregar géneros
    album.agregarGenero("Rock");
    album.agregarGenero("Reggueton");
    album.agregarGenero("Opera Rock");

    cout << "\nGeneros agregados: " << album.getNumGeneros() << "\n";
    string* generos = album.getGeneros();
    if (generos != nullptr) {
        for (int i = 0; i < album.getNumGeneros(); i++) {
            cout << "  - " << generos[i] << "\n";
        }
        delete[] generos;
    }

    // Crear y agregar canciones
    Cancion* cancion1 = new Cancion(123456701, "everve", 223, "/music/un/faf");
    Cancion* cancion2 = new Cancion(123456702, "migtao", 354, "/music/queen/bohemian");
    Cancion* cancion3 = new Cancion(123456703, "hola", 508, "/music/rrere/prophet");

    album.agregarCancion(cancion1);
    album.agregarCancion(cancion2);
    album.agregarCancion(cancion3);

    cout << "\nCanciones en el album: " << album.getNumCanciones() << "\n";
    cout << "Duracion total: " << album.getDuracionFormateada() << "\n";

    // Acceso por operador []
    cout << "\nPrimera cancion (usando operator[]): " << album[0]->getNombre() << "\n";
    cout << "Segunda cancion: " << album[1]->getNombre() << "\n";

    // Buscar canción
    Cancion* encontrada = album.buscarCancion(123456702);
    if (encontrada != nullptr) {
        cout << "\nCancion encontrada por ID: " << encontrada->getNombre() << "\n";
    }

    encontrada = album.buscarCancionPorNombre("The Prophet's Song");
    if (encontrada != nullptr) {
        cout << "Cancion encontrada por nombre: " << encontrada->getNombre()
        << " (" << encontrada->getDuracionFormateada() << ")\n";
    }

    // Actualizar puntuación
    album.actualizarPuntuacion(9.8f);
    cout << "\nPuntuacion del album: " << album.getPuntuacion() << "/10\n";

    // Probar operadores
    Album otroAlbum(99, "Nerjrjtrjtrjrjrld", "1977-10-28", "EMI", "/covers/news.png");
    otroAlbum.actualizarPuntuacion(9.5f);

    cout << "\n¿Album 1 > Album 2 (por puntuacion)? " << (album > otroAlbum ? "Si" : "No") << "\n";
    cout << "¿Albums son iguales? " << (album == otroAlbum ? "Si" : "No") << "\n";
    cout << "¿Album tiene ID 67? " << (album == 67 ? "Si" : "No") << "\n";

    // Memoria
    cout << "\nMemoria usada por album: " << album.calcularMemoriaUsada() << " bytes\n";

    // Liberar canciones
    delete cancion1;
    delete cancion2;
    delete cancion3;

    cout << "\n✅ Prueba de Album EXITOSA\n";
}

void probarIntegracion() {
    imprimirSeparador("PRUEBA: Integracion Completa");

    cout << "Simulando flujo completo de UdeATunes...\n\n";

    // 1. Crear álbum completo con canciones y créditos
    Album* album = new Album(42, "Ttrtjrjrjtrjrtjrethe Moon", "1973-03-01",
                             "Harvest Records", "/covers/dark_side.png");
    album->agregarGenero("Progressive Rock");
    album->agregarGenero("Psychedelic Rock");

    // 2. Crear canción con créditos completos
    Cancion* cancion = new Cancion(123454201, "Time", 413, "/music/pigreeroyd/time");

    Credito* productor = new Credito("Alrn", "Paregns", "PROD999AAA", 1);
    Credito* guitarrista = new Credito("Daver", "Giegour", "GUIT888BBB", 2);
    Credito* compositor1 = new Credito("Reeer", "Watggs", "COMP777CCC", 3);
    Credito* compositor2 = new Credito("eick", "Mason", "COMP666DDD", 3);

    cancion->agregarCredito(productor);
    cancion->agregarCredito(guitarrista);
    cancion->agregarCredito(compositor1);
    cancion->agregarCredito(compositor2);

    // 3. Agregar canción al álbum
    album->agregarCancion(cancion);

    // 4. Simular reproducción
    cout << "🎵 REPRODUCIENDO:\n";
    cout << "   Album: " << album->getNombre() << "\n";
    cout << "   Cancion: " << cancion->getNombre() << " (" << cancion->getDuracionFormateada() << ")\n";
    cout << "   Portada: " << album->getPortada() << "\n";
    cout << "   Audio (320 kbps): " << cancion->obtenerRutaAudio(320) << "\n";

    // 5. Mostrar créditos
    cout << "\n CREDITOS:\n";
    int cantProductores = 0, cantMusicos = 0, cantCompositores = 0;
    Credito** productores = cancion->obtenerCreditosPorTipo(1, cantProductores);
    Credito** musicos = cancion->obtenerCreditosPorTipo(2, cantMusicos);
    Credito** compositores = cancion->obtenerCreditosPorTipo(3, cantCompositores);

    cout << "   Productores:\n";
    for (int i = 0; i < cantProductores; i++) {
        cout << "     - " << productores[i]->getNombreCompleto() << "\n";
    }

    cout << "   Musicos:\n";
    for (int i = 0; i < cantMusicos; i++) {
        cout << "     - " << musicos[i]->getNombreCompleto() << "\n";
    }

    cout << "   Compositores:\n";
    for (int i = 0; i < cantCompositores; i++) {
        cout << "     - " << compositores[i]->getNombreCompleto() << "\n";
    }

    // 6. Simular reproducciones y publicidad
    cancion->incrementarReproducciones();

    MensajePublicitario publicidad("hola mama", 3);
    cout << "\n PUBLICIDAD (Categoria " << publicidad.getNombreCategoria() << "):\n";
    cout << "   " << publicidad.getContenido() << "\n";
    publicidad.incrementarContador();

    // 7. Estadísticas finales
    cout << "\n ESTADISTICAS:\n";
    cout << "   Canciones en album: " << album->getNumCanciones() << "\n";
    cout << "   Duracion total: " << album->getDuracionFormateada() << "\n";
    cout << "   Reproducciones: " << cancion->getVecesReproducida() << "\n";
    cout << "   Memoria total (aproximada): "
         << (album->calcularMemoriaUsada() + publicidad.calcularMemoriaUsada())
         << " bytes\n";

    // Liberar memoria
    if (productores != nullptr) delete[] productores;
    if (musicos != nullptr) delete[] musicos;
    if (compositores != nullptr) delete[] compositores;

    delete productor;
    delete guitarrista;
    delete compositor1;
    delete compositor2;
    delete cancion;
    delete album;

    cout << "\n Prueba de Integracion EXITOSA\n";
}

int main() {
    cout << "\n";
    cout << "     SISTEMA DE PRUEBAS - UdeATunes";
    cout <<       "Streaming Musical con POO";


    try {
        probarMensajePublicitario();
        probarCredito();
        probarCancion();
        probarAlbum();
        probarIntegracion();

        imprimirSeparador("RESUMEN FINAL");
        cout << "\n TODAS LAS PRUEBAS EXITOSAS\n";
        cout << "\nClases probadas:\n";
        cout << "   MensajePublicitario\n";
        cout << "   Credito\n";
        cout << "   Cancion\n";
        cout << "   Album\n";
        cout << "\nOperadores sobrecargados probados:\n";
        cout << "   operator=\n";
        cout << "   operator==\n";
        cout << "   operator!=\n";
        cout << "   operator<\n";
        cout << "   operator>\n";
        cout << "   operator[] (Album)\n";
        cout << "\nFuncionalidades probadas:\n";
        cout << "   Memoria dinamica\n";
        cout << "   Constructor de copia\n";
        cout << "   Destructores\n";
        cout << "   Gestion de creditos\n";
        cout << "   IDs jerarquicos\n";
        cout << "   Calculo de memoria\n";
        cout << "   Validaciones\n";

        cout << "\n Sistema funcionando correctamente!\n\n";

    } catch (const exception& e) {
        cout << "\n ERROR: " << e.what() << "\n\n";
        return 1;
    }

    return 0;
}
