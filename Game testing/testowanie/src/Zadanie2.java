import static org.junit.Assert.assertThrows;
import static org.mockito.Mockito.doThrow;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.when;
import static org.mockito.Mockito.verify;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.ArgumentCaptor;
import org.mockito.Captor;
import org.mockito.junit.jupiter.MockitoExtension;

@ExtendWith(MockitoExtension.class)
class Zadanie2{

    @Captor
    private ArgumentCaptor<Exception> messageCaptor;

    @Test
    void test() throws SessionOpenException {
        Session s = mock(Session.class);
        GenericDAO d = new GenericDAO(s);
        d.save();
    }
    @Test
    void testthrowOpen() throws SessionOpenException {
        Session s = mock(Session.class);
        when(s.open()).thenThrow(new SessionOpenException());
        GenericDAO d = new GenericDAO(s);
        assertThrows(SessionOpenException.class, () -> {
            d.save();
        });
    }
    @Test
    void testthrowCommit() throws CommitException, SessionOpenException {
        Session s = mock(Session.class);
        doThrow(CommitException.class).when(s).commitTransaction();
        GenericDAO d = new GenericDAO(s);
        d.save();
        verify(d.dblog, times(1)).log(messageCaptor.capture());
    }
}