<div align="center">
  <h1>🍴 Fork</h1>

  <p>
    <strong>Sistemas Operativos (7508) - FIUBA</strong><br>
    Laboratorio sobre manejo de procesos (fork), tuberías (pipes) y descriptores de archivo en UNIX.
  </p>

  <img src="https://img.shields.io/badge/Language-C-00599C?style=flat-square&logo=c&logoColor=white" alt="Lenguaje C">
  <img src="https://img.shields.io/badge/Platform-Linux-FCC624?style=flat-square&logo=linux&logoColor=black" alt="Plataforma Linux">
  <img src="https://img.shields.io/badge/Tools-Docker-2496ED?style=flat-square&logo=docker&logoColor=white" alt="Docker">
  <img src="https://img.shields.io/badge/Build-Makefile-000000?style=flat-square&logo=gnu-make&logoColor=white" alt="Makefile">

  <br>

  <img src="Terminal.png" alt="Ejecución en Terminal" width="80%" style="border-radius: 10px; box-shadow: 0px 4px 10px rgba(0,0,0,0.2);">
</div>

---

## 📋 Descripción

Este proyecto contiene la implementación de dos utilidades fundamentales para entender la concurrencia en UNIX:

1.  **`primes`**: Generador de números primos concurrentes utilizando la Criba de Eratóstenes mediante procesos enlazados por *pipes*.
2.  **`xargs`**: Implementación de la utilidad estándar que construye y ejecuta líneas de comandos a partir de la entrada estándar.

## 💻 Programas

### 1. Primes (`primes.c`)
Implementación de la Criba de Eratóstenes concurrente para generar números primos. El proceso principal genera una secuencia de números y crea una cadena de procesos filtradores conectados por *pipes*.

**Uso:**

```bash
./primes <N>
```

**Ejemplo:**

```bash
./primes 35
# Salida esperada:
# primo 2
# primo 3
# ...
# primo 31
```

### 2. Xargs (`xargs.c`)

Implementación simplificada de la utilidad estándar xargs. Lee argumentos desde la entrada estándar (stdin) y ejecuta un comando específico pasando dichos argumentos en bloques (por defecto, bloques de 4 argumentos definidos por NARGS).

**Uso:**

```bash
./xargs <comando>
```

**Ejemplo:**

```bash
# Imprime los números del 1 al 10 agrupados
seq 10 | ./xargs echo
```

## 🚀 Compilación y Desarrollo

### Compilar

**Para generar los binarios primes y xargs:**

```bash
make
```

**Limpiar binarios**

```bash
make clean
```

**Formato de código**

El proyecto utiliza clang-format para mantener el estilo de código del curso:

```bash
make format
```

## 🛠 Pruebas (Testing)

El repositorio cuenta con un sistema de pruebas automatizado en Python (tests/) que verifica tanto la lógica de los programas como el manejo de memoria con Valgrind.
Ejecutar pruebas (Docker)

La forma recomendada de correr las pruebas es utilizando el entorno Docker provisto, lo cual asegura que las herramientas necesarias (como Valgrind y Python 3) estén disponibles.

```Bash
make test
```

Esto construirá una imagen Docker llamada fisop-fork y ejecutará los tests dentro de ella.

## 👥 Integrantes

| Integrante | Padrón | Contacto |
| :--- | :---: | :---: |
| **Calderón Vasil, Máximo Augusto** | 111810 | [![GitHub](https://img.shields.io/badge/GitHub-black?style=flat-square&logo=github)](https://github.com/maxivasil) [![Email](https://img.shields.io/badge/Email-red?style=flat-square&logo=gmail&logoColor=white)](mailto:mcalderonv@fi.uba.ar) |