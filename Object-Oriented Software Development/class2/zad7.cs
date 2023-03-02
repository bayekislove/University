public class Student {
    USOSWebPage us;
    public void xxx(){
        us.show();
    };
};

public class USOSWebPage {
    GradeController gc;
    public void show(Student st){
        pageLayout = gc.getStudentGradeInfo(st);
    }
};

public class GradeController {
    public void getStudentGradeInfo(Student st){
        course[] courses = st.getCourses();
        for(course c : courses){
            mark = c.getMark(st);
        }
    }
};

public class course {
    int[] mark {get; set;}
    public int getMark(Student st){
        return mark for st;
    }
};