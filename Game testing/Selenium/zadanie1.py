from selenium.webdriver import Chrome
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import Select
def areAllFieldsClear():
    myFields = driver.find_elements(By.XPATH, "//input")
    for field in myFields :
       if(field.get_attribute("value") == "text" and field.get_attribute("value") != ""):
            return False
    return True


driver = Chrome()
# wchodzimy na stronę główną google
driver.get("D:\\University\\Game testing\\Selenium\\page\\index.html")
lnks=driver.find_elements_by_tag_name("a")
# traverse list
for lnk in lnks:
   if "contact.html" in lnk.get_attribute('href'):
        obj = lnk
obj.click()
print(areAllFieldsClear())
element = driver.find_element(By.XPATH, "//input[@name='name']")
element.send_keys("Jakub")
element = driver.find_element(By.XPATH, "//input[@name='surname']")
element.send_keys("Szajner")
element = driver.find_element(By.XPATH, "//input[@name='email']")
element.send_keys("123@gmail.com")
select = Select(driver.find_element(By.ID, 'country'))
select.select_by_index(1)
element = driver.find_element(By.XPATH, "//textarea[@name='message']")
element.send_keys("lorem ipsum")
driver.save_screenshot('screenie.png')
element.submit()
alert = driver.switch_to.alert
alert.accept()
# driver.find_element(By.XPATH, "//a[@href=contact.html]")
# element = driver.find_element(By.ID, "passwd-id")