# System Programming

This repository contains a compilation of laboratory assignments from the System Programming course, focusing on the C language within the Linux operating system.

## Лабораторна робота №5

### Завдання

Написати програму, яка створює файл заданого розміру за допомогою:

a. Низькорівневих функцій вводу-виводу;
b. Стандартних функцій для роботи з файлами мови C;
c. Функції `mmap()`.

Також виконати копіювання вихідного файлу в новий файл із заданим ім’ям також трьома способами. Обчислити час створення та копіювання файлу кожним способом. Розміри файлу в залежності від варіанту:

1. Шість гігабайт.
2. Два гігабайта.
3. Три гігабайта.
4. Чотири гігабайта.
5. П’ять гігабайт.

Ваш варіант: 2 (Два гігабайта)

### Створення файлу

#### Створення файлу за допомогою низькорівневих функцій вводу-виводу

```bash

make create_lowlevel

```

![Template Create With Lowlevel](./public/assets/create_lowlevel.png)

#### Створення файлу за допомогою стандартних функцій для роботи з файлами мови С

```bash

make create_standard

```

![Template Create With Standard](./public/assets/create_standard.jpg)

#### Створення файлу за допомогою функції mmap().

```bash

make create_mmap

```

![Template Create With MMap](./public/assets/create_mmap.jpg)

### Копіювання файлу

#### Копіювання файлу за допомогою низькорівневих функцій вводу-виводу

```bash

make copy_lowlevel

```

![Template Copy With Lowlevel](./public/assets/copy_lowlevel.jpg)

#### Копіювання файлу за допомогою стандартних функцій для роботи з файлами мови С

```bash

make copy_standard

```

![Template Copy With Standard](./public/assets/copy_standard.jpg)

#### Копіювання файлу за допомогою функції mmap().

```bash

make copy_mmap

```

![Template Copy With MMap](./public/assets/copy_mmap.jpg)
