[PYTHON]
import logging
import os
import re
import shutil
import subprocess
import tarfile
from configparser import ConfigParser
from threading import Thread
from time import sleep
from typing import List, Optional

from console_logger import ConsoleLogger
from file_logger import FileLogger
from node import Node
from ssh_session import SSHSession


class SOSCollector:
    def __init__(self, config: ConfigParser, nodes: List[Node]):
        self.config = config
        self.nodes = nodes
        self.archive: Optional[str] = None
        self.logfile: FileLogger = FileLogger('sos-collector')
        self.console_log_file: FileLogger = ConsoleLogger()
        self.logger = logging.getLogger(__name__)
        self._init_logs()

    def _init_logs(self):
        log_level = self.config['DEFAULT']['log_level']
        formatter = '%(asctime)s - %(levelname)s - %(message)s'
        file_handler = FileLogger('sos-collector', formatter=formatter, level=log_level)
        self.logger.addHandler(file_handler)
        console_handler = ConsoleLogger(formatter=formatter, level=log_level)
        self.logger.addHandler(console_handler)

    def collect(self):
        """Collect sosreports from all nodes."""
        self.console_log_file.info('Beginning collection of sosreports...')
        pool = ThreadPoolExecutor(self.config['threads'])
        pool.map(self._collect, self.nodes)
        pool.shutdown(wait=True)
        if hasattr(self.config['cluster'], 'run_extra_cmd'):
            self.console_log_file.info('Collecting additional data from master node...')
            f = self.config['cluster'].run_extra_cmd()
            if f:
                self.master.collect_extra_cmd(f)
        msg = '\nSuccessfully captured %s of %s sosreports'
        self.log_info(msg % (self.retrieved, self.report_num))
        if self.retrieved > 0:
            self.create_cluster_archive()
        else:
            msg = 'No sosreports were collected, nothing to archive...'
            self._exit(msg, 1)
        self.close_all_connections()

    def _collect(self, node):
        """Runs sosreport on each node."""
        if not node.local:
            node.sosreport()
        else:
            if not self.config['no_local']:
                node.sosreport()
        if node.retrieved:
            self.retrieved += 1

    def close_all_connections(self):
        """Close all ssh sessions for nodes."""
        for node in self.nodes:
            self.log_debug('Closing SSH connection to %s' % node.address)
            node.close_ssh_session()

    def create_cluster_archive(self):
        """Calls for creation of tar archive then cleans up the temporary files created by sos-collector."""
        self.log_info('Creating archive of sosreports...')
        self.create_sos_archive()
        if self.archive:
            self.logger.info('Archive created as %s' % self.archive)
            self.cleanup()
            self.console_log_file.info('\nThe following archive has been created. Please provide it to your support team.')
            self.console_log_file.info('    %s' % self.archive)

    def create_sos_archive(self):
        """Creates a tar archive containing all collected sosreports."""
        try:
            self.archive = self._get_archive_path()
            with tarfile.open(self.archive, "w:gz") as tar:
                for fname in os.listdir(self.config['tmp_dir']):
                    arcname = fname
                    if fname == self.logfile.name.split('/')[-1]:
                        arcname = 'sos-collector.log'
                    if fname == self.console_log_file.name.split('/')[-1]:
                        arcname = 'sos-collector-console.log'
                    tar.add(os.path.join(self.config['tmp_dir'], fname), arcname=arcname)
        except Exception as e:
            self.logger.exception('Error creating sos-collector archive')

    def cleanup(self):
        """Cleans up the temporary files created by sos-collector."""
        try:
            shutil.rmtree(self.config['tmp_dir'])
        except Exception as e:
            self.logger.exception('Error cleaning up temporary files')

    def _get_archive_path(self):
        """Returns the path where the sos-collector archive should be saved."""
        return os.path.join(os.getcwd(), 'sos-collector-{}.tar.gz'.format(int(subprocess.check_output(['date', '+%s']).decode().strip())))

    def log_info(self, message):
        """Logs an informational message."""
        self.logger.info(message)

    def log_debug(self, message):
        """Logs a debug message."""
        self.logger.debug(message)
[/PYTHON]
