/*
 * date.h
 *
 */

#ifndef DATE_H_
#define DATE_H_

#include <stdio.h>
#include <time.h> // time_t, struct tm, funções de tempo
#include <stdbool.h> // tipo bool, valores true, false
#include <stdlib.h> // malloc, free
#include <string.h> // operações com string

/*
 * Enumerador das partes de uma data
 */
enum DateComponent{
    MDAY, //dia do mês
    YDAY, // dia do ano
    WDAY, // dia da semana (0: domingo, 6: sábado)
    MONTH, // mês
    YEAR, // ano
    HOUR, // hora (formato 24 horas)
    HOUR_AMPM, // hora (formato am/pm)
    MINUTE, // minutos
    SECOND // segundos
};

/*
 * Enumerador do formato da data
 */
enum DateString{
    DATE_DMY, // dd/mm/yyyy
    DATE_YMD, // yyyy/mm/dd
    DATE_HMS, // h:m:s 24 hours
    DATE_HMS_AMPM, // h:m:s am/pm format
    DATE_DMY_HMS, // dd/mm/yyyy h:m:s 24 hours
    DATE_YMD_HMS, // yyyy/mm/dd h:m:s 24 hours
    DATE_DMY_HMS_AMPM, // dd/mm/yyyy h:m:s am/pm format
    DATE_YMD_HMS_AMPM  // yyyy/mm/dd h:m:s am/pm format
};

/*
 * Enumerador das partes da semana
 */
enum WeekComponent{
    SUNDAY, // domingo
    MONDAY, // segunda
    TUESDAY, // terça
    WEDNESDAY, // quarta
    THURSDAY, // quinta
    FRIDAY, // sexta
    SATURDAY // sábado
};

/*
 * Estrutura do objeto data
 *
 * Armazena data e hora
 */
typedef struct date Date;

/* ******************************************
 * Funções de Data
 ********************************************/

/*
 * Cria a Data
 * Aloca memória para um objeto Date e
 * retorna um ponteiro para a memória alocada
 */
Date* createDate();

/*
 * Desaloca objeto Date, e retorna NULL
 *
 * Date* date : ponteiro para objeto Date a ser desalocado
 */
Date* destroyDate(Date* date);

/*
 * Configura a data para hoje
 *
 * Date* Date : ponteiro para objeto Date a ter a data configurada
 */
void setDateToday(Date* date);

/*
 * Configura uma data específica
 * Retorna true se conseguir, e false caso contrário (a data não é válida)
 *
 * Date* date : ponteiro para objeto Date a ter a data configurada
 * int day : dia do mês
 * int month : mês
 * int year : ano
 */
bool setDatePartial(Date* date, int day, int month, int year);

/*
 * Configura a data completa
 * Retorna true se conseguir, e false caso contrário (a data não é válida)
 *
 * Date* date : ponteiro para objeto Date a ter a data configurada
 * int day : dia do mês
 * int month : mês
 * int year: ano
 * int hour : hora
 * int minute : minuto
 * int second : segundo
 */
bool setDateComplete(Date* date, int day, int month, int year,
        int hour, int minute, int second);

/*
 * Define a data dos segundos a partir de 1900
 * Retorna true se conseguir, e false caso contrário
 *
 * Date* date : ponteiro para objeto Date a ter a data configurada
 * time_t seconds : segundos desde 1900
 */
bool setDateOfSeconds(Date* date, time_t seconds);

/*
 * Retorna a data em segundos desde 1900
 *
 * Date* date : ponteiro para objeto Date
 */
time_t getDateInSeconds(Date* date);

/*
 * Retorna um componente da data (dia, mês, ano, hora ...)
 * Retorna -1 se, por algum motivo, não conseguir retorna o solicitado
 *
 * Date* date : ponteiro para objeto Date
 * enum DateComponent dateComponent : enumerador que indica a parte da data
 *      a ser retornada (veja o enumerador neste header file)
 *
 * Obs: alguns retornos específicos:
 * dia do mês: 1 - 31
 * dia do ano: 1 - 365
 * dia da semana: 0(para domingo) - 6(para sábado)
 * mês: 1-12
 * hora: 0-23
 * hora_ampm: 1-12
 * outros: formatos esperados
 */
int getDateComponent(Date* date, enum DateComponent dateComponent);

/*
 * Gera uma string e guarda o resultado na memória onde o ponteiro fornecido
 * aponta
 * Retorna false se não conseguir
 *
 * Date* date : ponteiro para objeto Date
 * emun DateString dateString : enumerador que indica qual o formato da string
 *      a ser utilizado (veja o enumerador neste header file)
 * bool weekDayName : se o nome do dia da semana deve constar no final da string
 * char* dateStringComp : ponteiro para string literal
 *
 * Obs: para char = 1byte, considere que a área de memória para onde o ponteiro
 * da string literal aponta tenha pelo menos 40 bytes.
 */
bool getStringDate(Date* date, enum DateString dateString,
        bool weekDayName, char* dateStringComp);

/*
 * Gera uma string do dia da semana e o retorna
 *
 * Date* date : ponteiro para o objeto Date
 * char* dateStringComp : ponteiro para string literal
 *
 * Obs: para char = 1byte, considere que a área de memória para onde o ponteiro
 * da string literal aponta tenha pelo menos 10 bytes.
 */
bool getStringWeekDay(Date* date, char* stringComp);

/*
 * Adiciona (ou subtrai) uma quantidade em uma componente específica da data
 * Retorna false se não conseguir, e true em caso contrário
 *
 * Date* date : ponteiro para o objeto Date
 * enum DateComponent dateComponent : enumerador que indica a parte da data
 *      a ser operado (veja o enumerador neste header file)
 * int value : valor a ser adicionado (ou subtraído) na componente de data
 * bool add : se true, adiciona. se false, subtrai
 *
 * Obs: se estiver no dia 29 de fevereiro em um ano dissexto e adicionar uma quantidade de
 * anos que resulte em um ano não bissexto, o resultado será em uma data diferente de 29 de
 * fevereiro. O mesmo acontece quando adicionamos meses e estamos no dia 31 (afinal, nem todos os
 * meses possuem 31 dias) ou mesmo 30 e caímos em fevereiro (que tem 28/29 dias).
 */
bool addComponentDate(Date* date, enum DateComponent dateComponent, int value, bool add);

/*
 * Imprime no prompt a data em um formato pré-especificado
 *
 * Date* date : ponteiro para objeto Date
 * emun DateString dateString : enumerador que indica qual o formato da string
 *      a ser utilizado (veja o enumerador neste header file)
 * bool weekDayName : se o nome do dia da semana deve constar no final da string
 */
void printDate(Date* date, enum DateString dateString, bool weekDayName);

/*
 * Imprime o nome do dia da semana no prompt
 *
 * Date* date : ponteiro para o objeto Date
 */
void printWeekDate(Date* date);

/*
 * Verifica se uma data é válida
 * Retorna false em caso negativo
 *
 * int day : dia
 * int month : mês
 * int year : ano
 * int hour : hora
 * int minute : minuto
 * int second : segundo
 */
bool validateDate(int day,int month,int year,int hour,int minute,int second);

#endif /* DATE_H_ */
