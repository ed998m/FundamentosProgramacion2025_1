cmake_minimum_required(VERSION 3.20)
project(Simulador_Caida_CanSat C)

set(CMAKE_C_STANDARD 99)

add_executable(Simulador_Caida_CanSat
    main.c
    entrada_datos.c
    simulacion.c
    atmósfera.c
    interfaz.c
        simrandom.c
)