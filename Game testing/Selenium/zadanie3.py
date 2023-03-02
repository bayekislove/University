from selenium.webdriver import Chrome
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import Select

driver = Chrome()
# wchodzimy na stronę główną google
driver.get("https://en.wikipedia.org")
element=driver.find_element_by_id("searchInput")
element.send_keys("python")
element.submit()
lnks=driver.find_elements_by_tag_name("a")
for lnk in lnks:
    link = lnk.get_attribute('href')
    if link is not None and "python" in link.lower() and "#" not in link:
        driver.execute_script('''window.open("'''+ lnk.get_attribute('href') +'''","_blank");''')
        parent = driver.window_handles[0]
        chld = driver.window_handles[1]
        driver.switch_to.window(chld)
        print(driver.title)
        for paragraph in driver.find_elements(by=By.TAG_NAME, value="p"):
            if paragraph.text != "":
                print(paragraph.text)
                break
        driver.close()
        driver.switch_to.window(parent)
