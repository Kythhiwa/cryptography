
# Установка зависимостей 

## Ubuntu/Debian

```
sudo apt update
sudo apt install libgmp-dev
sudo apt install libgtest-dev

```
# Основная программа 

## Сборка

```
cmake -B build -S .

cmake --build build 
```

## Запуск 

```
./build/prog <m> <q> <qd1> <qd2> ... <qdn>

```

## Запуск эксперимента

```
./build/experiment

```

# Тесты

## Сборка

```
cs tests/
cmake -B build -S .
cmake --build build 

```

## Запуск

```
./build/Testing
```
