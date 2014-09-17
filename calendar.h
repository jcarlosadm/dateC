/*
 * calendar.h
 *
 */

#ifndef CALENDAR_H_
#define CALENDAR_H_

#include <stdio.h>
#include <time.h> // time_t, struct tm, funções de tempo
#include <stdbool.h> // tipo bool, valores true, false
#include <stdlib.h> // malloc, free

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
 * Estrutura do objeto calendário
 *
 * Armazena data e hora
 */
typedef struct calendar Calendar;

/* ******************************************
 * Funções do calendário
 ********************************************/

/*
 * Cria o calendário
 * Aloca memória para um objeto Calendar e
 * retorna um ponteiro para a memória alocada
 */
Calendar* createCalendar();

/*
 * Desaloca objeto Calendar, e retorna NULL
 *
 * Calendar* calendar : ponteiro para objeto Calendar a ser desalocado
 */
Calendar* destroyCalendar(Calendar* calendar);

/*
 * Configura a data do calendário para hoje
 *
 * Calendar* calendar : ponteiro para objeto Calendar a ter a data configurada
 */
void setDateToday(Calendar* calendar);

/*
 * Configura uma data específica no calendário
 * Retorna true se conseguir, e false caso contrário
 *
 * Calendar* calendar : ponteiro para objeto Calendar a ter a data configurada
 * int day : dia do mês
 * int month : mês
 * int year : ano
 */
bool setDatePartial(Calendar* calendar, int day, int month, int year);

/*
 * Configura a data completa do calendário
 * Retorna true se conseguir, e false caso contrário
 *
 * Calendar* calendar : ponteiro para objeto Calendar a ter a data configurada
 * int day : dia do mês
 * int month : mês
 * int year: ano
 * int hour : hora
 * int minute : minuto
 * int second : segundo
 */
bool setDateComplete(Calendar* calendar, int day, int month, int year,
        int hour, int minute, int second);

/*
 * Define a data dos segundos a partir de 1900
 * Retorna true se conseguir, e false caso contrário
 *
 * Calendar* calendar : ponteiro para objeto Calendar a ter a data configurada
 * time_t seconds : segundos desde 1900
 */
bool setDateOfSeconds(Calendar* calendar, time_t seconds);

/*
 * Retorna a data do calendário em segundos desde 1900
 *
 * Calendar* calendar : ponteiro para objeto Calendar
 */
time_t getDateInSeconds(Calendar* calendar);

/*
 * Retorna um componente do calendário (dia, mês, ano, hora ...)
 * Retorna -1 se, por algum motivo, não conseguir retorna o solicitado
 *
 * Calendar* calendar : ponteiro para objeto Calendar
 * enum DateComponent dateComponent : enumerador que indica a parte do calendário
 *      a ser retornado (veja o enumerador neste header file)
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
int getDateComponent(Calendar* calendar, enum DateComponent dateComponent);

/*
 * Gera uma string e retorna um ponteiro para essa string
 *
 * Calendar* calendar : ponteiro para objeto Calendar
 * emun DateString dateString : enumerador que indica qual o formato da string
 *      a ser utilizado (veja o enumerador neste header file)
 * bool weekDayName : se o nome do dia da semana deve constar no final da string
 */
char* getStringDate(Calendar* calendar, enum DateString dateString,
        bool weekDayName);

/*
 * Gera uma string do dia da semana e o retorna
 *
 * Calendar* calendar : ponteiro para o objeto Calendar
 */
char* getStringWeekDay(Calendar* calendar);

/*
 * Adiciona (ou subtrai) uma quantidade em uma componente específica da data
 * Retorna false se não conseguir, e true em caso contrário
 *
 * Calendar* calendar : ponteiro para o objeto Calendar
 * enum DateComponent dateComponent : enumerador que indica a parte do calendário
 *      a ser operado (veja o enumerador neste header file)
 * int value : valor a ser adicionado (ou subtraído) na componente de data
 * bool add : se true, adiciona. se false, subtrai
 */
bool addComponentDate(Calendar* calendar, enum DateComponent dateComponent, int value, bool add);

/*
 * Imprime no prompt a data em um formato pré-especificado
 *
 * Calendar* calendar : ponteiro para objeto Calendar
 * emun DateString dateString : enumerador que indica qual o formato da string
 *      a ser utilizado (veja o enumerador neste header file)
 * bool weekDayName : se o nome do dia da semana deve constar no final da string
 */
void printDate(Calendar* calendar, enum DateString dateString, bool weekDayName);

/*
 * Imprime o nome do dia da semana no prompt
 *
 * Calendar* calendar : ponteiro para o objeto Calendar
 */
void printWeekDate(Calendar* calendar);

#endif /* CALENDAR_H_ */
