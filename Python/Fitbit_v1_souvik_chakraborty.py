#using fitbit unoffical API
import fitbit
import gather_keys_oauth2 as Oauth2
import pandas as pd
import datetime
CLIENT_ID = '22CZR5' 
CLIENT_SECRET = '25b7c8d16f68ba7feb9d6f03897608c4' 
server = Oauth2.OAuth2Server(CLIENT_ID, CLIENT_SECRET)
server.browser_authorize()
ACCESS_TOKEN = str(server.fitbit.client.session.token['access_token'])
REFRESH_TOKEN = str(server.fitbit.client.session.token['refresh_token'])
auth2_client = fitbit.Fitbit(CLIENT_ID, CLIENT_SECRET, Oauth2=True, access_token=ACCESS_TOKEN, refresh_token=REFRESH_TOKEN)
yesterday = str((datetime.datetime.now() - datetime.timedelta(days=1)).strftime("%Y%m%d"))
yesterday2 = str((datetime.datetime.now() - datetime.timedelta(days=1)).strftime("%Y-%m-%d"))
today = str(datetime.datetime.now().strftime("%Y%m%d"))
today2 = str(datetime.datetime.now().strftime("%Y-%m-%d"))
fit_statsHR = auth2_client.intraday_time_series('activities/heart', base_date=today2, detail_level='1sec')
time_list = []
val_list = []
for i in fit_statsHR['activities-heart-intraday']['dataset']:
    val_list.append(i['value'])
    time_list.append(i['time'])
heartdf = pd.DataFrame({'Heart Rate':val_list,'Time':time_list})
heartdf.to_csv('/Users/Souvik/Documents/classes/PROJECT/data/heart'+ \
               today2+'.csv', \
               columns=['Time','Heart Rate'], header=True, index = False)
fit_statsSl = auth2_client.sleep(date='today')    #has to be today;data synced with server every 1 minute...that's the server pre-defined
print(fit_statsSl)
stime_list = []
sval_list = []
for i in fit_statsSl['sleep'][0]['minuteData']:
    stime_list.append(i['dateTime'])
    sval_list.append(i['value'])
    
sleepdf = pd.DataFrame({'State':sval_list,
                     'Time':stime_list})
sleepdf['Interpreted'] = sleepdf['State'].map({'2':'Awake','3':'Very Awake','1':'Asleep'})
print(sleepdf)
sleepdf.to_csv('/Users/Souvik/Documents/classes/PROJECT/data/sleep' + \
               today+'.csv', \
               columns = ['Time','State','Interpreted'],header=True, 
               index = False)
#end of code

                   
