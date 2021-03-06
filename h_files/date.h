/**
 * \file date.h
 * Módulo que descreve como criar e manipular uma data
 */

#ifndef DATE_H_
#define DATE_H_

#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * Enumerador das partes de uma data
 */
enum DateComponent{
    MDAY, ///<dia do mês
    YDAY, ///< dia do ano
    WDAY, ///< dia da semana (0: domingo, 6: sábado)
    MONTH, ///< mês
    YEAR, ///< ano
    HOUR, ///< hora (formato 24 horas)
    HOUR_AMPM, ///< hora (formato am/pm)
    MINUTE, ///< minutos
    SECOND ///< segundos
};

/**
 * Enumerador do formato da data
 */
enum DateString{
    DATE_DMY, ///< dd/mm/yyyy
    DATE_YMD, ///< yyyy/mm/dd
    DATE_HMS, ///< h:m:s 24 hours
    DATE_HMS_AMPM, ///< h:m:s am/pm format
    DATE_DMY_HMS, ///< dd/mm/yyyy h:m:s 24 hours
    DATE_YMD_HMS, ///< yyyy/mm/dd h:m:s 24 hours
    DATE_DMY_HMS_AMPM, ///< dd/mm/yyyy h:m:s am/pm format
    DATE_YMD_HMS_AMPM  ///< yyyy/mm/dd h:m:s am/pm format
};

/**
 * Enumerador das partes da semana
 */
enum WeekComponent{
    SUNDAY, ///< domingo
    MONDAY, ///< segunda
    TUESDAY, ///< terça
    WEDNESDAY, ///< quarta
    THURSDAY, ///< quinta
    FRIDAY, ///< sexta
    SATURDAY ///< sábado
};

/**
 * Estrutura do objeto data
 * Armazena data e hora
 */
typedef struct date Date;

/**
 * Cria a Data
 * Aloca memória para um objeto Date
 * \return Ponteiro para objeto Date
 */
Date* createDate();

/**
 * Desaloca objeto Date
 * \return NULL
 * \param date Ponteiro para objeto Date a ser desalocado
 */
Date* destroyDate(Date* date);

/**
 * Configura a data para a data atual
 * \param date Ponteiro para objeto Date a ter a data configurada
 */
void setDateToday(Date** date);

/**
 * Configura uma data específica
 * \return true se conseguir, e false caso contrário (a data não é válida)
 * \param date Ponteiro para objeto Date a ter a data configurada
 * \param day Dia do mês
 * \param month Mês
 * \param year Ano
 */
bool setDatePartial(Date** date, int day, int month, int year);

/**
 * Configura a data completa
 * \return true se conseguir, e false caso contrário (a data não é válida)
 * \param date Ponteiro para objeto Date a ter a data configurada
 * \param day Dia do mês
 * \param month Mês
 * \param year Ano
 * \param hour Hora
 * \param minute Minuto
 * \param second Segundo
 */
bool setDateComplete(Date** date, int day, int month, int year,
        int hour, int minute, int second);

/**
 * Define a data dos segundos a partir de 1900
 * \return true se conseguir, e false caso contrário
 * \param date Ponteiro para objeto Date a ter a data configurada
 * \param seconds Segundos desde 1900
 */
bool setDateOfSeconds(Date** date, time_t seconds);

/**
 * Retorna a data em segundos desde 1900
 * \return Segundos desde 1900
 * \param date Ponteiro para objeto Date
 */
time_t getDateInSeconds(Date** date);

/**
 * Retorna um componente da data (dia, mês, ano, hora ...)
 * \return -1 se, por algum motivo, não conseguir retorna o solicitado<BR>
 * Alguns retornos específicos:<BR>
 * &nbsp; &nbsp; dia do mês: 1 - 31<BR>
 * &nbsp; &nbsp; dia do ano: 1 - 365<BR>
 * &nbsp; &nbsp; dia da semana: 0(para domingo) - 6(para sábado)<BR>
 * &nbsp; &nbsp; mês: 1-12<BR>
 * &nbsp; &nbsp; hora: 0-23<BR>
 * &nbsp; &nbsp; hora_ampm: 1-12<BR>
 * &nbsp; &nbsp; outros: formatos esperados
 * \param date Ponteiro para objeto Date
 * \param dateComponent Enumerador que indica a parte da data
 *      a ser retornada (veja o enumerador neste header file)
 */
int getDateComponent(Date** date, enum DateComponent dateComponent);

/**
 * Gera uma string e guarda o resultado na memória onde o ponteiro fornecido
 * aponta<BR>
 * Obs: para char = 1byte, considere que a área de memória para onde o ponteiro
 * da string literal aponta tenha pelo menos 40 bytes.
 * \return false se não conseguir, true em caso contrário
 * \param date Ponteiro para objeto Date
 * \param dateString Enumerador que indica qual o formato da string
 *      a ser utilizado (veja o enumerador neste header file)
 * \param weekDayName Se o nome do dia da semana deve constar no final da string
 * \param dateStringComp Ponteiro para string literal a ser modificada
 */
bool getStringDate(Date** date, enum DateString dateString,
        bool weekDayName, char* dateStringComp);

/**
 * Gera uma string do dia da semana e o retorna<BR>
 * Obs: para char = 1byte, considere que a área de memória para onde o ponteiro
 * da string literal aponta tenha pelo menos 10 bytes.
 * \return true se bem sucedido, false em caso contrário
 * \param date Ponteiro para o objeto Date
 * \param dateStringComp Ponteiro para string literal
 */
bool getStringWeekDay(Date** date, char* stringComp);

/**
 * Adiciona (ou subtrai) uma quantidade em uma componente específica da data<BR>
 * Obs: se estiver no dia 29 de fevereiro em um ano dissexto e adicionar uma quantidade de
 * anos que resulte em um ano não bissexto, o resultado será em uma data diferente de 29 de
 * fevereiro. O mesmo acontece quando adicionamos meses e estamos no dia 31 (afinal, nem todos os
 * meses possuem 31 dias) ou mesmo 30 e caímos em fevereiro (que tem 28/29 dias).
 * \return false se não conseguir, e true em caso contrário
 * \param date Ponteiro para o objeto Date
 * \param dateComponent Enumerador que indica a parte da data
 *      a ser operado (veja o enumerador neste header file)
 * \param value Valor a ser adicionado (ou subtraído) na componente de data
 * \param add Se true, adiciona. se false, subtrai
 */
bool addComponentDate(Date** date, enum DateComponent dateComponent, int value, bool add);

/**
 * Imprime no prompt a data em um formato pré-especificado
 * \param date Ponteiro para objeto Date
 * \param dateString Enumerador que indica qual o formato da string
 *      a ser utilizado (veja o enumerador neste header file)
 * \param weekDayName Se o nome do dia da semana deve constar no final da string
 */
void printDate(Date** date, enum DateString dateString, bool weekDayName);

/**
 * Imprime o nome do dia da semana no prompt
 * \param date Ponteiro para o objeto Date
 */
void printWeekDate(Date** date);

/**
 * Verifica se uma data é válida
 * \return false em caso negativo
 * \param day Dia
 * \param month Mês
 * \param year Ano
 * \param hour Hora
 * \param minute Minuto
 * \param second Segundo
 */
bool validateDate(int day,int month,int year,int hour,int minute,int second);

#endif /* DATE_H_ */
