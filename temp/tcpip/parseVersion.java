import java.io.BufferedReader;
import java.io.FileReader;

public class parseVersion
{
    public static void main(String[] args)
    {
    }
    public static String[][] parseVersionLWIP(Object component, String sdk_path)
    {
        String[][] result = new String[2][2];
        String s32sdkpath = System.getenv(sdk_path);
        String version_major = null;
        String version_minor = null;
        String version_revision = null;
        try
        {
        	BufferedReader br = new BufferedReader(new FileReader(s32sdkpath+"/middleware/tcpip/lwip/src/include/lwip/init.h"));
            String line = br.readLine();
            while (line != null)
            {
                if(line.matches("(.*)#define(.*)"+"LWIP_VERSION_MAJOR"+"(.*)[0-9](.*)"))
                {
                    String linep = line.replaceAll("\\s+", "|");
                    String[] fields = linep.split("\\|");
                    if (fields.length == 3)
                    {
                        version_major = fields[2];
                    }
                    else if (fields.length == 4)
                    {
                        version_major = fields[3];
                    }
                }
                if(line.matches("(.*)#define(.*)"+"LWIP_VERSION_MINOR"+"(.*)[0-9](.*)"))
                {
                    String linep = line.replaceAll("\\s+", "|");
                    String[] fields = linep.split("\\|");
                    if (fields.length == 3)
                    {
                        version_minor = fields[2];
                    }
                    else if (fields.length == 4)
                    {
                        version_minor = fields[3];
                    }
                }
                if(line.matches("(.*)#define(.*)"+"LWIP_VERSION_REVISION"+"(.*)[0-9](.*)"))
                {
                    String linep = line.replaceAll("\\s+", "|");
                    String[] fields = linep.split("\\|");
                    if (fields.length == 3)
                    {
                        version_revision = fields[2];
                    }
                    else if (fields.length == 4)
                    {
                        version_revision = fields[3];
                    }
                }
                line = br.readLine();
            }
            br.close();
            /* macro-commands to execute */
            result[1][0] = "%set LWIPVERSION Value "+version_major+"."+version_minor+"."+version_revision;
        }
        catch(Exception e)
        {
            version_major = null;
            version_minor = null;
            version_revision = null;
            e.printStackTrace();
        }
        return result;
    }
}