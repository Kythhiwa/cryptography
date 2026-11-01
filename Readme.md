
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
./build/prog

```


# Тесты

## Сборка

```
cmake -B build -S .
cmake --build build 

```

## Запуск

```
./build/Testing
```
