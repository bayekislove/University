package filesystemApp;

import java.io.File;
import java.nio.file.Files;
import java.nio.file.Paths;

public class appLogic 
{
    File currentFile;
    File currentDirectory;
    filesList listLogic;

    public appLogic(filesList listLogic)
    {
        this.listLogic = listLogic;
        currentDirectory = new File("C://");
    }

    public void markFile(int index)
    {
        currentFile = (File)listLogic.getElementAt( index );
    }

    public void changeDirectory(File newDirectory)
    {
        if( newDirectory.isDirectory() )
        {
            currentDirectory = newDirectory;
            listLogic.changeDirectory(newDirectory);
        }
    }

    public void copyFile() 
    {
        if(currentFile == null) return;
        try
        {
            Files.copy(currentFile.toPath(), Paths.get( currentDirectory.toPath() + "//-C" + currentFile.getName() ));
            listLogic.changeDirectory(currentDirectory);
        }
        catch(Exception e) { };
	}

    public void deleteFile() 
    {
        if(currentFile == null) return;
        try
        {
            Files.delete( Paths.get( currentFile.getAbsolutePath() ) );
            listLogic.changeDirectory( this.currentDirectory );
        }
        catch (Exception exception) {  }
	}

    public void rename(String newName) 
    {
        if(currentFile == null) return;
        currentFile.renameTo( new File( currentDirectory.getAbsolutePath() + "//" + newName ) );
        listLogic.changeDirectory( this.currentDirectory );
	}

    public void recode(encoding enc) 
    {

	}
}