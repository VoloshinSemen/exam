from django.conf.urls import url

from . import views
from .views import MytableListView
from .views import updateRecord
from .views import deleteRecord
from .views import addRecord
from .views import deleteRecord
from .views import cancel
from .views import createRecord

urlpatterns = [
    url(r'^$', MytableListView.as_view(), name='UgraMed'),
    url(r'^(?P<record_id>[0-9]+)/updateRecord/$', views.updateRecord, name='updateRecord'),
    url(r'^(?P<record_id>[0-9]+)/deleteRecord/$', views.deleteRecord, name='deleteRecord'),
    url(r'^/addRecord/$', views.addRecord, name='addRecord'),
    url(r'^/createRecord/$', views.createRecord, name='createRecord'),
    url(r'^/cancel/$', views.cancel, name='cancel'),
]
