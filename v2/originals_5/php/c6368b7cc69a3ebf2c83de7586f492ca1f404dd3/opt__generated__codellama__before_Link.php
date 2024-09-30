<?php
namespace Pimcore\Model\DataObject\Data;

use Pimcore\Model;
use Pimcore\Tool;

class Link implements Model\Element\Interfaces\Value {
    protected $data = [];

    public function __construct($data = []) {
        if (is_array($data)) {
            $this->setDataFromResource($data);
        } elseif (is_string($data)) {
            $this->setHref($data);
        }
    }

    public function getHref() {
        if (!empty($this->data['href'])) {
            return $this->data['href'];
        }

        if ($this->data['internal']) {
            if ($this->data['internalType'] == 'document') {
                if ($doc = Document::getById($this->data['internalId'])) {
                    return $doc->getFullPath();
                }
            } elseif ($this->data['internalType'] == 'asset') {
                if ($asset = Asset::getById($this->data['internalId'])) {
                    return $asset->getFullPath();
                }
            } elseif ($this->data['internalType'] == 'object') {
                if ($object = Model\DataObject\Concrete::getById($this->data['internalId'])) {
                    return $object->getFullPath();
                }
            }
        }

        return '';
    }

    public function setHref($href) {
        $this->data['href'] = $href;
        return $this;
    }

    public function getData() {
        return $this->data;
    }

    public function setData($data) {
        if (is_array($data)) {
            $this->setDataFromResource($data);
        } elseif (is_string($data)) {
            $this->setHref($data);
        }
    }

    public function getDataForResource() {
        return \Pimcore\Tool\Serialize::serialize($this->getData());
    }

    public function getDataForEditmode() {
        $data = [
            'path' => $this->getHref(),
            'linktype' => 'internal',
            'internalType' => 'document',
            'internalId' => null,
            'internal' => false,
        ];

        if ($this->data['internal']) {
            $data['internalType'] = $this->data['internalType'];
            $data['internalId'] = $this->data['internalId'];
            $data['internal'] = true;
        }

        return $data;
    }

    public function setDataFromResource($data) {
        $this->data = \Pimcore\Tool\Serialize::unserialize($data);
        if (!is_array($this->data)) {
            $this->data = [];
        }

        return $this;
    }

    public function setDataFromEditmode($data) {
        if (!is_array($data)) {
            $data = [];
        }

        $path = $data['path'] ?? null;

        if (!empty($path)) {
            $target = null;

            if ($data['linktype'] == 'internal' && $data['internalType']) {
                $target = Model\Element\Service::getElementByPath($data['internalType'], $path);
                if ($target) {
                    $data['internal'] = true;
                    $data['internalId'] = $target->getId();
                }
            }

            if (!$target) {
                if ($target = Document::getByPath($path)) {
                    $data['internal'] = true;
                    $data['internalId'] = $target->getId();
                    $data['internalType'] = 'document';
                } elseif ($target = Asset::getByPath($path)) {
                    $data['internal'] = true;
                    $data['internalId'] = $target->getId();
                    $data['internalType'] = 'asset';
                } elseif ($target = Model\DataObject\Concrete::getByPath($path)) {
                    $data['internal'] = true;
                    $data['internalId'] = $target->getId();
                    $data['internalType'] = 'object';
                }
            }
        }

        return $this;
    }

    public function isEmpty() {
        return empty($this->data);
    }

    public function rewriteIds($sourceDocument, $targetDocument) {
        if ($this->data['internal']) {
            if ($this->data['internalType'] == 'document') {
                $sourceDocument = Document::getById($sourceDocument);
                $targetDocument = Document::getById($targetDocument);
                $idMap = [];
                $idMap[$sourceDocument->getId()] = $targetDocument->getId();
                if ($this->data['internalType'] == 'document') {
                    $idMap[$sourceDocument->getId()] = $targetDocument->getId();
                }
                return \Pimcore\Tool\Serialize::rewriteIds($this->data, $idMap);
            } elseif ($this->data['internalType'] == 'asset') {
                $sourceDocument = Asset::getById($sourceDocument);
                $targetDocument = Asset::getById($targetDocument);
                $idMap = [];
                $idMap[$sourceDocument->getId()] = $targetDocument->getId();
                if ($this->data['internalType'] == 'asset') {
                    $idMap[$sourceDocument->getId()] = $targetDocument->getId();
                }
                return \Pimcore\Tool\Serialize::rewriteIds($this->data, $idMap);
            } elseif ($this->data['internalType'] == 'object') {
                $sourceDocument = Model\DataObject\Concrete::getById($sourceDocument);
                $targetDocument = Model\DataObject\Concrete::getById($targetDocument);
                $idMap = [];
                $idMap[$sourceDocument->getId()] = $targetDocument->getId();
                if ($this->data['internalType'] == 'object') {
                    $idMap[$sourceDocument->getId()] = $targetDocument->getId();
                }
                return \Pimcore\Tool\Serialize::rewriteIds($this->data, $idMap);
            }
        }
    }
}
