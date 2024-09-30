 
[PYTHON]
# This code will generate a page for the user to view and edit their filters.
from datetime import datetime
import random

with open('filter_form_draw_inputs.txt', 'r') as f:
    filter_form_draw_inputs = f.read()

with open('filter_print_view_type_toggle.txt', 'r') as f:
    filter_print_view_type_toggle = f.read()

# Define a dictionary to store the filters and their properties
filters = {
    1: {'name': 'Filter 1', 'created_by': 1, 'created_on': datetime(2021, 9, 1), 'modified_by': None, 'modified_on': None, 'search': '', 'status': False},
    2: {'name': 'Filter 2', 'created_by': 1, 'created_on': datetime(2021, 9, 1), 'modified_by': None, 'modified_on': None, 'search': '', 'status': True},
    3: {'name': 'Filter 3', 'created_by': 1, 'created_on': datetime(2021, 9, 1), 'modified_by': None, 'modified_on': None, 'search': '', 'status': False}
}

# Define a list to store the filter IDs and names
filter_ids = [1, 2, 3]
filter_names = ['Filter 1', 'Filter 2', 'Filter 3']

# Define a dictionary to store the fields and their properties for each filter
fields = {
    1: {'name': 'Name', 'search': True, 'status': False},
    2: {'name': 'Created by', 'search': False, 'status': True},
    3: {'name': 'Created on', 'search': False, 'status': True}
}

# Define a list to store the field IDs and names for each filter
field_ids = [1, 2, 3]
field_names = ['Name', 'Created by', 'Created on']

layout_page_begin('Filter Page')

print("""
<div class="space-10"></div>
<div class="widget-box">
    <div class="widget-header widget-header-small">
        <h4 class="widget-title lighter">
            Filter Form
        </h4>
    </div>
    <form action="" method="post" enctype="multipart/form-data" onsubmit="return filter_form_validate();">
        <div class="widget-body">
            <div class="widget-main no-padding">
                <!-- Filters -->
                <div class="table-responsive">
                    {filter_form_draw_inputs}
                </div>
                <!-- End of Filters -->

                <!-- Fields -->
                <div class="table-responsive">
                    {filter_form_draw_fields}
                </div>
                <!-- End of Fields -->

                <!-- Search and Update Button -->
                <div class="widget-toolbox padding-8 clearfix">
                    <div class="btn-toolbar pull-left">
                        <button type="submit" class="btn btn-primary btn-sm btn-white btn-round no-float">Update</button>
                    </div>
                </div>
                <!-- End of Search and Update Button -->
            </div>
        </div>
    </form>
</div>
""".format(filter_form_draw_inputs=filter_form_draw_inputs, filter_form_draw_fields=''))

layout_page_end()
 [/PYTHON]
