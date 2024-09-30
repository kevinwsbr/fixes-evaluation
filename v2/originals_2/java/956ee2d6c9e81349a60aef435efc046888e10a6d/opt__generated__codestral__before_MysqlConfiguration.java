import org.apache.commons.text.StringEscapeUtils;

public String getJdbc() {
    StringBuilder urlBuilder = new StringBuilder("jdbc:mysql://");
    urlBuilder.append(StringEscapeUtils.escapeJava(getHost().trim()));
    urlBuilder.append(":");
    urlBuilder.append(StringEscapeUtils.escapeJava(getPort().toString().trim()));
    urlBuilder.append("/");
    urlBuilder.append(StringEscapeUtils.escapeJava(getDataBase().trim()));

    if(!StringUtils.isEmpty(extraParams.trim())){
        urlBuilder.append("?");
        urlBuilder.append(StringEscapeUtils.escapeJava(getExtraParams().trim()));
    }

    return urlBuilder.toString();
}
