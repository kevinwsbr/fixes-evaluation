@Override
protected XMLLoad createXMLLoad() {
    return new XMLLoadImpl(createXMLHelper()) {
        @Override
        public void load(XMLResource resource, InputStream inputStream, Map<?, ?> options) throws IOException {
            try {
                super.load(resource, inputStream, options);
            } catch (Exception e) {
                throw new IOException("Error occurred while loading the XML resource.", e);
            }
        }
    };
}
