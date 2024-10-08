```java
public class JBPMBpmn2ResourceImpl extends Bpmn2ResourceImpl {

    public HashMap xmlNameToFeatureMap = new HashMap();

	public JBPMBpmn2ResourceImpl(URI uri) {
		super(uri);
        this.getDefaultLoadOptions().put(XMLResource.OPTION_DEFER_IDREF_RESOLUTION, true);
        this.getDefaultLoadOptions().put(XMLResource.OPTION_DISABLE_NOTIFY, true);
        this.getDefaultLoadOptions().put(XMLResource.OPTION_USE_XML_NAME_TO_FEATURE_MAP, xmlNameToFeatureMap);

        // Switch off DTD external entity processing
        Map parserFeatures = new HashMap();
        parserFeatures.put("http://xml.org/sax/features/external-general-entities", false);
        this.getDefaultLoadOptions().put(XMLResource.OPTION_PARSER_FEATURES, parserFeatures);

        this.getDefaultSaveOptions().put(XMLResource.OPTION_ENCODING, "UTF-8");
        this.getDefaultSaveOptions().put(XMLResource.OPTION_PROCESS_DANGLING_HREF, XMLResource.OPTION_PROCESS_DANGLING_HREF_DISCARD);
	}
	
	@Override
    protected XMLSave createXMLSave() {
        prepareSave();
        return new JBPMXMLSaveImpl(createXMLHelper()) {
            @Override
            protected boolean shouldSaveFeature(EObject o, EStructuralFeature f) {
                return super.shouldSaveFeature(o, f);
            }
        };
    }

    @Override
    protected XMLLoad createXMLLoad() {
//        DroolsPackageImpl.init();
//        BpsimPackageImpl.init();
        return new XMLLoadImpl(createXMLHelper()) {

            @Override
            public void load(XMLResource resource, InputStream inputStream, Map<?, ?> options) throws IOException {
                try {
                    super.load(resource, inputStream, options);
                }
                catch (Exception e) {
                    DiagnosticWrappedException error = new DiagnosticWrappedException(e);
                    resource.getErrors().add(error);
                }
            }
        };
    }

    class DiagnosticWrappedException extends WrappedException implements Resource.Diagnostic {
        private static final long serialVersionUID = 1L;
        private String location;
        private int column;
        private int line;

        public DiagnosticWrappedException(Exception exception) {
            super(exception);
        }

        public void setLocation(String location) {
            this.location = location;
        }

        public String getLocation() {
            return location;
        }

        public void setColumn(int column) {
            this.column = column;;
        }

        public int getColumn() {
            return column;
        }

        public void setLine(int line) {
            this.line = line;
        }

        public int getLine() {
            return line;
        }
    }
