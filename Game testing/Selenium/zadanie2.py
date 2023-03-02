from selenium.webdriver import Chrome
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import Select
from selenium.webdriver.chrome.options import Options
from urllib import request
import os
chrome_options = Options()
chrome_options.add_argument("--headless")

driver = Chrome(options=chrome_options)

driver.get("C:\\Projekty\\University\\Testownaie\\Selenium\\page\\index.html")
lnks=driver.find_elements_by_tag_name("a")
for lnk in lnks:
   if "gallery.html" in lnk.get_attribute('href'):
        obj = lnk
obj.click()
isExist = os.path.exists("images")
lnks=driver.find_elements_by_tag_name("img")
if not isExist:
    os.mkdir("images")
for img in lnks:
    src = img.get_attribute('src')
    name = src.split('/')
    file = name[len(name)-1]
    request.urlretrieve(src,filename="C:\\Projekty\\University\\Testownaie\\Selenium\\images\\"+file)