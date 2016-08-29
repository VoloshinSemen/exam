from django.shortcuts import render
from django.template import loader

from django.views.generic.list import ListView
from django.utils import timezone

from django.shortcuts import get_object_or_404, render
from django.http import HttpResponseRedirect, HttpResponse
from django.core.urlresolvers import reverse

from .models import Mytable

class MytableListView(ListView):

    model = Mytable

    def get_context_data(self, **kwargs):
        context = super(MytableListView, self).get_context_data(**kwargs)
        context['now'] = timezone.now()
        return context
    
def updateRecord(request, record_id):
        p = get_object_or_404(Mytable, pk=record_id)
        p.a = request.POST['a' + str(record_id)]
        p.b = request.POST['b' + str(record_id)]
        p.c = request.POST['c' + str(record_id)]
        p.save()
        return HttpResponseRedirect(reverse('UgraMed'))

def deleteRecord(request, record_id):
    p = get_object_or_404(Mytable, pk=record_id)
    p.delete()
    return HttpResponseRedirect(reverse('UgraMed'))

def addRecord(request):
    template = loader.get_template('polls/addRecord.html')
    return HttpResponse(template.render({}, request))

def createRecord(request):
    p = Mytable()
    p.a = request.POST['a']
    p.b = request.POST['b']
    p.c = request.POST['c']
    p.save()
    return HttpResponseRedirect(reverse('UgraMed'))

def cancel(request):
    return HttpResponseRedirect(reverse('UgraMed'))
