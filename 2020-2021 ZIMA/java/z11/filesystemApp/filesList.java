package filesystemApp;

import java.io.File;
import java.io.FileFilter;
import java.util.Arrays;

import javax.swing.AbstractListModel;

public class filesList extends AbstractListModel
{
    File[] fileTab;

    public filesList(File inp)
    {
        obtainProperFileTab(inp);
    }

    @Override
    public int getSize() { return fileTab.length; }

    @Override
    public Object getElementAt(int index) { return fileTab[index]; };

    public void changeDirectory(File inp)
    {
        obtainProperFileTab(inp);
        this.fireContentsChanged( this, 0, this.getSize() - 1 );
    }
    
    public void obtainProperFileTab(File inp)
    {
        File[] files = inp.listFiles(new FileFilter()
        {
			@Override
            public boolean accept(File pathname) 
            {
				return pathname.isFile();
			}
        });
        if( files != null) Arrays.sort(files);

        File[] directories = inp.listFiles(new FileFilter()
        {
			@Override
            public boolean accept(File pathname) 
            {
				return pathname.isDirectory();
			}
        });
        if( files != null) Arrays.sort(directories);

        if(directories == null && files == null) return;

        int startIndex = ( inp.getParent() == null ? 0 : 1 );
        
        fileTab = new File[files.length + directories.length + startIndex];

        if(inp.getParent() != null) fileTab[0] = new File( inp.getParent() );

        if(directories.length == 0)
            System.arraycopy(files, 0, fileTab, startIndex, files.length);

        else if(files.length == 0)
            System.arraycopy(directories, 0, fileTab, startIndex, directories.length);

        else
        {
            System.arraycopy(directories, 0, fileTab, startIndex, directories.length);
            System.arraycopy(files, 0, fileTab, directories.length + startIndex, files.length);
        }
    }
}