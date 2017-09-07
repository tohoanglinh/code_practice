import java.io.BufferedReader;
import java.io.FileReader;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class parseVersion
{
    /* parse version of FreeRTOS_C55 */
    public static String[][] parseVersionFreertosC55(Object component, String sdkpath)
    {
        String sdk_path = System.getenv(sdkpath);
        String derivative = "FreeRTOS_C55";
        String freertos_path = sdk_path+"/rtos/"+derivative+"/Source/include/task.h";
        String version_major = null;
        String version_minor = null;
        String version_build = null;
        String[][] result = new String[2][1];

        /* parse version of FreeRTOS */
        version_major = parseDefine(freertos_path, "tskKERNEL_VERSION_MAJOR");
        version_minor = parseDefine(freertos_path, "tskKERNEL_VERSION_MINOR");
        version_build = parseDefine(freertos_path, "tskKERNEL_VERSION_BUILD");

        /* debug in java */
        System.out.println("%set @Link1@FreeRtosVersion Value "+version_major+"."+version_minor+"."+version_build);

        /* macro-commands to execute in macro language for processor expert */
        result[1][0] = "%set @Link1@FreeRtosVersion Value "+version_major+"."+version_minor+"."+version_build;
        return result;
    }

    /* parse version of lwIP */
    public static String[][] parseVersionLwip(Object component, String sdkpath)
    {
        String sdk_path = System.getenv(sdkpath);
        String lwip_path = sdk_path+"/middleware/tcpip/lwip/src/include/lwip/init.h";
        String version_major = null;
        String version_minor = null;
        String version_revision = null;
        String[][] result = new String[2][1];

        /* parse version of lwIP */
        version_major = parseDefine(lwip_path, "LWIP_VERSION_MAJOR");
        version_minor = parseDefine(lwip_path, "LWIP_VERSION_MINOR");
        version_revision = parseDefine(lwip_path, "LWIP_VERSION_REVISION");

        /* debug in java */
        System.out.println("%set LWIPVERSION Value "+version_major+"."+version_minor+"."+version_revision);

        /* macro-commands to execute in macro language for processor expert */
        result[1][0] = "%set LWIPVERSION Value "+version_major+"."+version_minor+"."+version_revision;
        return result;
    }

    public static String parseRegExp(String filePath, String patternString)
    {
        try (BufferedReader br = new BufferedReader(new FileReader(filePath)))
        {
            Pattern pattern = Pattern.compile(patternString);
            String line = null;
            while ((line = br.readLine()) != null)
            {
                Matcher matcher = pattern.matcher(line);
                if (matcher.find())
                {
                    return matcher.group(1);
                }
            }
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

        return null;
    }

    public static String parseDefine(String filePath, String symbol)
    {
        return parseRegExp(filePath, "#define\\s+" + symbol + "\\s+([^\\s]+)");
    }
}