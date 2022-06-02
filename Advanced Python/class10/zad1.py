import numpy
import wwo_hist
import os
import pandas
import requests

import matplotlib.pyplot as plt
import matplotlib.dates as mdates

from datetime import date, datetime, timedelta

API_KEY = "ed4df74a36914c3eaab193958211612"

os.chdir(".")

def plotTwoPeriods(startDate, endDate):
    startDateObj = datetime.strptime(startDate, "%d-%b-%Y")
    endDateObj = datetime.strptime(endDate, "%d-%b-%Y")

    wwo_hist.retrieve_hist_data(API_KEY, ['warsaw'], startDate, endDate, 24, export_csv=True)
    tempC = pandas.read_csv("warsaw.csv")["tempC"].tolist() #we have temperatures in a list
    open("covid.csv", "wb").write(requests.get("https://covid19.who.int/WHO-COVID-19-global-data.csv").content)

    covid = pandas.read_csv("covid.csv")
    cases = covid.loc[covid["Country_code"] == "PL"]
    startIndex = numpy.where(cases["Date_reported"] == startDateObj.strftime("%Y-%m-%d"))[0][0]
    endIndex = numpy.where(cases["Date_reported"] == endDateObj.strftime("%Y-%m-%d"))[0][0] + 1
    cases = cases.iloc[startIndex:endIndex]["New_cases"].values #now we have only covid cases in a list
    
    daysRange = mdates.drange(startDateObj, endDateObj + timedelta(days=1), timedelta(days=1))

    fig, tempPlot = plt.subplots()

    tempPlot.set_ylabel("TEMP in C degrees", color='tab:blue')
    tempPlot.plot(daysRange, tempC)
    tempPlot.tick_params(axis='y', labelcolor='tab:blue')

    casesPlot = tempPlot.twinx()

    casesPlot.set_ylabel("COVID-19 cases", color='tab:green')
    casesPlot.plot(daysRange, cases, color='tab:green')
    casesPlot.tick_params(axis='y', labelcolor='tab:green')

    plt.gca().xaxis.set_major_formatter(mdates.DateFormatter('%Y-%m-%d'))
    plt.gca().xaxis.set_major_locator(mdates.DayLocator(interval=10))
    plt.gcf().autofmt_xdate()
    fig.tight_layout()

    plt.show()

plotTwoPeriods("01-MAY-2021","30-JUL-2021")
plotTwoPeriods("01-SEP-2020","30-NOV-2020")
