import java.io.BufferedReader;
import java.io.FileReader;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class ParseVersionClass
{
    public static String[][] parseVersion(Object component, String params)
    {
        /* declare variables */
        String[][] result = new String[2][1];
        String[] param = null;
        String tool_path = null;
        String ver_major = null;
        String ver_minor = null;
        String ver_build = null;
        String pex_var = null;
        String version = null;

        /* slit and get parameter from a combined 'params' input */
        param = params.split(">>>");
        tool_path = System.getenv(param[0])+param[1];
        ver_major = param[2];
        ver_minor = param[3];
        ver_build = param[4];
        pex_var = param[5];

        /* parse version information from provided params */
        version = parseDefine(tool_path, ver_major)+"."+parseDefine(tool_path, ver_minor)+"."+parseDefine(tool_path, ver_build);
        /* macro-commands to execute in processor expert */
        result[1][0] ="%set "+pex_var+" Value "+version;

        /* must return result otherwise launchExt won't work */
        return result;
    }

    public static String parseDefine(String filePath, String symbol)
    {
        return parseRegExp(filePath, "#define\\s+" + symbol + "\\s+([^\\s]+)");
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
}
