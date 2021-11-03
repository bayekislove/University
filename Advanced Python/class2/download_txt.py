from urllib.request import urlopen
import ssl

def save_txt_in_list(url):
    ssl._create_default_https_context = ssl._create_unverified_context
    return urlopen(url).read().decode('utf-8')